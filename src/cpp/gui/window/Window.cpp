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
#include <phys/Player.h>

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

	std::cout << "Starting OpenGL Window" << std::endl;

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
	World* world = World::the();

	//test player
	Player* thePlayer = new Player(0,0,0);
	window->addKeyboardListener(thePlayer);
	window->addMouseListener(thePlayer);

	glm::vec3 lightDirection = glm::normalize(glm::vec3{ 0.0f, 0.5f, 1.0f });

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	//TODO - extract away from the window class
	PhysicsEngine* engine = PhysicsEngine::the();
	engine->addObject(&(* window->camera));
	engine->addObject(thePlayer);
	engine->addObject(&thePlayer->playerCam);
	engine->start();

	std::chrono::system_clock::time_point renderStartTime = std::chrono::system_clock::now();;
	std::chrono::system_clock::time_point renderEndTime = std::chrono::system_clock::now();;
	std::chrono::duration<double> currentFrameTime = renderEndTime - renderStartTime;

	//Test for chunk loader memory leak
	//ChunkLoader* loader = new ChunkLoader(new WorldGenerator(10));
	//for (int k = 0; k < 10; k++) {
	//	for (int i = 0; i < 50; i++) {
	//		for (int j = 0; j < 50; j++) {
	//			//loader->getChunk(i, j);
	//			ChunkRenderer* renderer = new ChunkRenderer(loader->getChunk(i, j));
	//			delete renderer;
	//		}
	//	}
	//	for (int i = 0; i < 50; i++) {
	//		for (int j = 0; j < 50; j++) {
	//			loader->removeChunk(i, j);
	//		}
	//	}
	//}
	
	
	std::cout << "Beginning render loop" << std::endl;

	while (!glfwWindowShouldClose(glfwWindow)) {

		renderStartTime = std::chrono::system_clock::now();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		thePlayer->update(currentFrameTime.count());
		thePlayer->render();

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

