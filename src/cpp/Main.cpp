// Voxel.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include <iostream>
#include <gui/window/Window.h>
#include <gui/shader/Shader.h>
#include <gui/shader/ShaderProgram.h>
#include <string>

int main() {

	std::cout << "Starting Voxel game engine..." << std::endl;

	//first init glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window::start();

	return 0;
}
