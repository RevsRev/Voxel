#include <phys/GameObject.h>

GameObject::GameObject(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void GameObject::updatePosition(float delTime) {
	x += delTime * xVel;
	y += delTime * yVel;
	z += delTime * zVel;
}

glm::vec3 &GameObject::getPosition() {
	return glm::vec3{ x,y,z };
}