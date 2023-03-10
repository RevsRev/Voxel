#pragma once

extern class PhysicsEngine;

class PhysicalObject {
private:
	double inertialMass = 1.0f;
	double gravitationalMass = 1.0f;

public:

	PhysicalObject(double x0, double y, double z);

	void doPhysics(double xForce, double yForce, double zForce, float delTime);
	void updatePosition(float delTime);

	double x;
	double y;
	double z;

	double xVel = 0.0f;
	double yVel = 0.0f;
	double zVel = 0.0f;

	friend PhysicsEngine;

};