#include "gui/window/Window.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gui/shader/Shader.h"
#include "gui/shader/ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"
#include "struc/Chunk.h"
#include "struc/World.h"
#include <chrono>
#include "gui/Camera.h"

#include "gui/draw/Attribute.h"
#include "gui/draw/VAO.h"
#include "gui/draw/VBO.h"

#include "gui/draw/ChunkRenderer.h"
#include "io/CallBack.h"

#include <phys/PhysicsEngine.h>

Window::Window(int width, int height) {
	init(width, height);
}

void Window::init(int width, int height) {
	window = glfwCreateWindow(width, height, "WindowName", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	initGlad();

	addMouseListener(camera);
	addKeyboardListener(camera);
}

void Window::initGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

Camera* Window::getCamera() {
	return camera;
}

//TODO - Thread safety + extract window size.
Window* Window::the() {
	static Window* theWindow = new Window(800, 600);
	return theWindow;
}

//TODO - ADD THIS BACK IN
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//		return;
//	}

void Window::start() {
	Window* window = the();
	GLFWwindow* glfwWindow = window->window;

	glfwSetFramebufferSizeCallback(glfwWindow, frameBufferSizeCallback);
	glfwSetCursorPosCallback(glfwWindow, CallBack::mouse_callback);
	glfwSetKeyCallback(glfwWindow, CallBack::keyboard_callback);


	//test projections
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 400.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	//test world
	World* world = new World();

	glm::vec3 lightDirection = glm::normalize(glm::vec3{ 0.0f, 0.5f, 1.0f });

	std::vector<ChunkRenderer*> renderers{};
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			ChunkRenderer* renderer = new ChunkRenderer(&world->chunks[i][j]);

			int modelLoc = renderer->getShaderProgram()->getUniformLocation("model");
			int viewLoc = renderer->getShaderProgram()->getUniformLocation("view");
			int projLoc = renderer->getShaderProgram()->getUniformLocation("projection");
			int lightDirLoc = renderer->getShaderProgram()->getUniformLocation("lightDirection");
			int camPosLoc = renderer->getShaderProgram()->getUniformLocation("cameraPosition");

			/*std::cout << "modelLoc: " << modelLoc << std::endl;
			std::cout << "viewLoc: " << viewLoc << std::endl;
			std::cout << "projLoc: " << projLoc << std::endl;
			std::cout << "lightDirLoc: " << lightDirLoc << std::endl;
			std::cout << "camPosLoc: " << camPosLoc << std::endl;*/

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDirection));
			glUniform3fv(lightDirLoc, 1, &lightDirection[0]);
			glUniform3fv(camPosLoc, 1, &(window->getCamera()->getPosition())[0]);
			//glUniform3fv(camPosLoc, 1, GL_FALSE, (*window->getCamera()->getPosition())[0]);

			renderer->getShaderProgram()->use(); //have to use to bind the new values (I think..?)

			renderers.push_back(renderer);
		}
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	//TODO - extract away from the window class
	PhysicsEngine* engine = PhysicsEngine::the();
	engine->addObject(&(* window->camera));
	engine->start();

	std::chrono::system_clock::time_point renderStartTime = std::chrono::system_clock::now();;
	std::chrono::system_clock::time_point renderEndTime = std::chrono::system_clock::now();;
	std::chrono::duration<double> currentFrameTime = renderEndTime - renderStartTime;

	while (!glfwWindowShouldClose(glfwWindow)) {

		renderStartTime = std::chrono::system_clock::now();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i<renderers.size(); i++) {

			ChunkRenderer* renderer = renderers.at(i);
			int vLoc = renderer->getShaderProgram()->getUniformLocation("view");
			int cpLoc = renderer->getShaderProgram()->getUniformLocation("cameraPosition");
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(window->camera->getView()));
			glUniform3fv(cpLoc, 1, &(window->getCamera()->getPosition())[0]);

			renderers.at(i)->render();
		}

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();

		renderEndTime = std::chrono::system_clock::now();
		std::chrono::duration<double> currentFrameTime = renderEndTime - renderStartTime;
	}

	engine->stop();
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

