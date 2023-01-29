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
	//frameBufferSizeCallback(window, width, height);
	Window* window = the();
	GLFWwindow* glfwWindow = window->window;

	glfwSetFramebufferSizeCallback(glfwWindow, frameBufferSizeCallback);
	/*glfwSetCursorPosCallback(glfwWindow, mouse_callback);*/
	glfwSetCursorPosCallback(glfwWindow, CallBack::mouse_callback);
	glfwSetKeyCallback(glfwWindow, CallBack::keyboard_callback);

	//test loading a shader
	std::string fragShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\fragment\\voxel.txt";
	std::string vertexShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\vertex\\voxel.txt";
	Shader* fragShader = Shader::fromFile(fragShaderPath.c_str(), GL_FRAGMENT_SHADER);
	Shader* vertexShader = Shader::fromFile(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	ShaderProgram* shaderProgram = new ShaderProgram();
	shaderProgram->addShader(fragShader);
	shaderProgram->addShader(vertexShader);
	shaderProgram->compile();

	//test projections
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	//test world
	World* world = new World();
	std::vector<float>* vcs = world->getVoxelPositionsToRender();
	int size = vcs->size();
	float* voxelPositions = new float[size];
	for (int i = 0; i < size; i++) {
		voxelPositions[i] = vcs->at(i);
	}

	//mera* camera = new Camera();

	shaderProgram->use();
	int modelLoc = glGetUniformLocation(shaderProgram->getId(), "model");
	int viewLoc = glGetUniformLocation(shaderProgram->getId(), "view");
	int projLoc = glGetUniformLocation(shaderProgram->getId(), "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	VAO* vao = new VAO();
	VBO* vboCube = new VBO(cubeVerticesWithTex, 5 * 6 * 6 * sizeof(float));
	VBO* vboInstanced = new VBO(voxelPositions, vcs->size() * sizeof(float));

	Attribute* attrVertex = new Attribute(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	Attribute* attrTex = new Attribute(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
	Attribute* attrInst = new Attribute(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	attrInst->setDivisor(1);

	vao->addVBO(vboCube);
	vboCube->addAttribute(attrVertex);
	vboCube->addAttribute(attrTex);
	vao->addVBO(vboInstanced);
	vboInstanced->addAttribute(attrInst);

	std::vector<ChunkRenderer*> renderers{};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			renderers.push_back(new ChunkRenderer(&world->chunks[i][j]));
		}
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//TODO - extract away from the window class
	PhysicsEngine* engine = PhysicsEngine::the();
	engine->addObject(&(* window->camera));
	engine->start();

	std::chrono::system_clock::time_point renderStartTime = std::chrono::system_clock::now();;
	std::chrono::system_clock::time_point renderEndTime = std::chrono::system_clock::now();;
	std::chrono::duration<double> currentFrameTime = renderEndTime - renderStartTime;

	while (!glfwWindowShouldClose(glfwWindow)) {

		renderStartTime = std::chrono::system_clock::now();

		//window->processInput((float)currentFrameTime.count());
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*window->camera->getView()));

		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i<renderers.size(); i++) {
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

