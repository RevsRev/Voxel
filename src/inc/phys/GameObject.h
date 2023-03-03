#pragma once

#include <glm/vec3.hpp>

extern class GameEngine;

class GameObject {
private:

public:

	GameObject(double x0, double y, double z);

	glm::vec3 &getPosition();
	void updatePosition(float delTime);

	double x;
	double y;
	double z;

	double xVel = 0.0f;
	double yVel = 0.0f;
	double zVel = 0.0f;

	friend GameEngine;

};