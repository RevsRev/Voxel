#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <io/KeyBoard.h>
#include <io/Mouse.h>
#include <GLFW/glfw3.h>
#include <io/KeyCache.h>
#include <phys/GameObject.h>
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

class Camera : public MouseListener, public KeyBoardListener {
private:
	//glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	
	//todo - these need fixing
	float movementSpeed = 1.0f;
	float pitchSpeed = 10.0f;
	float yawSpeed = 10.0f;
	float rollSpeed = 10.0f;
	
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	//For tracking mouse
	double lastX;
	double lastY;
	bool firstMouse = true;

	//for tracking keys
	KeyCache keyCache{};

	GameObject* trackedObject;

public:

	Camera(GameObject* trackedObject);

	//todo - make these return references, rather than copying values
	glm::vec3 getPosition();
	glm::vec3 getDirection();
	glm::mat4 getView();

	/*void moveRelativePos(glm::vec3 dir, float delTime);*/
	void rotateCamera(float delPitch, float delYaw, float delRoll, float delTime);

	void processKeyEvent(int key, int scancode, int action, int mods);
	void processMouseEvent(double xPos, double yPos);

};