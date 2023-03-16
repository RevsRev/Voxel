#include "gui/Camera.h"
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

Camera::Camera(GameObject* trackedObject) {
	this->trackedObject = trackedObject;
}

glm::vec3 Camera::getPosition() {
	return trackedObject->getPosition();
}
glm::vec3 Camera::getDirection() {
	//TODO - implement roll
	return direction;
}
glm::mat4 Camera::getView() {
	glm::vec3 position = getPosition();
	return glm::lookAt(position, position + direction, up);
}

void Camera::rotateCamera(float delPitch, float delYaw, float delRoll, float delTime) {
	float root = sqrt(delPitch * delPitch + delYaw * delYaw + delRoll * delRoll); //normalize the vals

	//TODO - extract epsilon
	if (abs(root) < 0.01f) {
		return;
	}

	pitch += pitchSpeed * delTime * delPitch/root;
	yaw += - yawSpeed * delTime * delYaw/root; //z axix points away from scrn, so need minus here
	roll += rollSpeed * delTime * delRoll/root;

	direction = glm::vec3(cos(pitch) * cos(yaw), cos(pitch) * sin(yaw), sin(pitch));
}

void Camera::processKeyEvent(int key, int scancode, int action, int mods) {
	
	//At the moment, don't care about repeat.
	if (action != GLFW_REPEAT) {
		keyCache.set(key, action);
	}

	int delX = 0;
	int delY = 0;
	int delZ = 0;
	if (keyCache.get(GLFW_KEY_W) == GLFW_PRESS) {
		delX += 1;
	}
	if (keyCache.get(GLFW_KEY_A) == GLFW_PRESS) {
		delY -= 1;
	}
	if (keyCache.get(GLFW_KEY_S) == GLFW_PRESS) {
		delX -= 1;
	}
	if (keyCache.get(GLFW_KEY_D) == GLFW_PRESS) {
		delY += 1;
	}
	if (keyCache.get(GLFW_KEY_SPACE) == GLFW_PRESS) {
		delZ += 1;
	}
	if (keyCache.get(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		delZ -= 1;
	}

	//TODO - refactor to make neater - should extract into a class for updating the postion of game objects, independent of if any cameras are looking at them
	if (delX != 0 || delY != 0 || delZ != 0) {
		glm::vec3 dir(delX, delY, delZ);
		glm::vec3 moveDir = dir.x * direction + dir.z * up + dir.y * glm::cross(direction, up);
		moveDir = glm::normalize(moveDir);
		glm::vec3 velocity = movementSpeed * moveDir;
		trackedObject->xVel = velocity.x;
		trackedObject->yVel = velocity.y;
		trackedObject->zVel = velocity.z;
	}
	else {
		trackedObject->xVel = 0;
		trackedObject->yVel = 0;
		trackedObject->zVel = 0;
	}
}
void Camera::processMouseEvent(double xPos, double yPos) {
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	float sensitivity = 10.0f; //TODO - remove at some point, as this doesn't do anything!
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	float delYaw = xoffset;
	float delPitch = yoffset;
		
	//TODO - remove the time component?
	rotateCamera(delPitch, delYaw, 0.0f, 0.01f);
}