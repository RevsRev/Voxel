#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <gui/Camera.h>

//TODO - Add exceptions when trying to bring up the windows in case of failure

extern void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
extern void mouse_callback(GLFWwindow* window, double xpos, double ypos);

class Window {
private:
	GLFWwindow* window;
	Camera* camera = new Camera();

	void init(int width, int height);
	void initGlad();
	void processInput(float delTime);

public:
	Window(int width, int height);
	Camera* getCamera();
	static Window* the();
	static void start();
};