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

//cube vertices with texture coords
static float vertices[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};
//float vertices[] = {
//	// first triangle
//	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // top right
//	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom right
//	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,// top left
//	// second triangle
//	0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom right
//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom left
//	- 0.5f, 0.5f, 0.0f, 0.0f, 0.0f // top left
//};

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

void Window::processInput(float delTime) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return;
	}

	int delX = 0;
	int delY = 0;
	int delZ = 0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		delX += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		delY -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		delX -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		delY += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		delZ += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		delZ -= 1;
	}
	
	if (delX != 0 || delY != 0 || delZ != 0) {
		camera->moveRelativePos(glm::vec3{ delX, delY, delZ }, delTime);
	}

}

void Window::start() {
	//frameBufferSizeCallback(window, width, height);
	Window* window = the();
	GLFWwindow* glfwWindow = window->window;

	glfwSetFramebufferSizeCallback(glfwWindow, frameBufferSizeCallback);
	glfwSetCursorPosCallback(glfwWindow, mouse_callback);

	//test loading a shader
	std::string fragShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\fragment\\fragment.txt";
	std::string vertexShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\vertex\\vertex.txt";
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
	std::vector<float>* vcs = world->getVerticesToRender();
	int size = vcs->size();
	float* arrVertices = new float[size];
	for (int i = 0; i < size; i++) {
		arrVertices[i] = vcs->at(i);
	}

	//mera* camera = new Camera();

	shaderProgram->use();
	int modelLoc = glGetUniformLocation(shaderProgram->getId(), "model");
	int viewLoc = glGetUniformLocation(shaderProgram->getId(), "view");
	int projLoc = glGetUniformLocation(shaderProgram->getId(), "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), arrVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
	glEnableVertexAttribArray(1);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::chrono::system_clock::time_point renderStartTime = std::chrono::system_clock::now();;
	std::chrono::system_clock::time_point renderEndTime = std::chrono::system_clock::now();;
	std::chrono::duration<double> currentFrameTime = renderEndTime - renderStartTime;

	while (!glfwWindowShouldClose(glfwWindow)) {

		renderStartTime = std::chrono::system_clock::now();

		window->processInput((float)currentFrameTime.count());
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(*window->camera->getView()));

		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram->use();
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/(5*sizeof(float)));
		glDrawArrays(GL_TRIANGLES, 0, size/5);

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();

		renderEndTime = std::chrono::system_clock::now();
		std::chrono::duration<double> currentFrameTime = renderEndTime - renderStartTime;
	}
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool firstMouse;
float lastX;
float lastY;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	float delYaw = xoffset;
	float delPitch = yoffset;

	//TODO - Pass in delTime
	Window::the()->getCamera()->rotateCamera(delPitch, delYaw, 0.0f, 0.1f);
}

