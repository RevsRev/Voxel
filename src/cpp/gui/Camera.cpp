#include "gui/Camera.h"
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"

glm::vec3* Camera::getPosition() {
	return &position;
}
glm::vec3* Camera::getDirection() {
	//TODO - implement roll
	return &direction;
}
glm::mat4* Camera::getView() {
	//glm::mat4* view = new glm::mat4(1.0f);
	//*view = glm::translate(*view, glm::vec3(0.0f, 0.0f, -3.0f));
	//return view;
	glm::mat4* view = new glm::mat4(1.0f);
	* view = glm::lookAt(position, position + direction, up);
	return view;
}


void Camera::moveRelativePos(glm::vec3 dir, float delTime) {
	glm::vec3 moveDir = dir.x * direction + dir.z * up + dir.y * glm::cross(direction, up);
	moveDir = glm::normalize(moveDir);

	position += delTime * movementSpeed * moveDir;
}
void Camera::rotateCamera(float delPitch, float delYaw, float delRoll, float delTime) {
	float root = sqrt(delPitch * delPitch + delYaw * delYaw + delRoll * delRoll); //normalize the vals
	pitch += pitchSpeed * delTime * delPitch/root;
	yaw += - yawSpeed * delTime * delYaw/root; //z axix points away from scrn, so need minus here
	roll += rollSpeed * delTime * delRoll/root;

	direction = glm::vec3(cos(pitch) * cos(yaw), cos(pitch) * sin(yaw), sin(pitch));
}
