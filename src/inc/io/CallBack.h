#pragma once
#include <gui/window/Window.h>
#include <glad/glad.h>

namespace CallBack {
	extern void mouse_callback(GLFWwindow* window, double xPos, double yPos);
	extern void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}