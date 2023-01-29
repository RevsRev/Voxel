#include <io/CallBack.h>

void CallBack::mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	Window::the()->publishMouse(xPos, yPos);
}
void CallBack::keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Window::the()->publishKeyboard(key, scancode, action, mods);
}