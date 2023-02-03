#include <phys/PhysicalObject.h>

PhysicalObject::PhysicalObject(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void PhysicalObject::doPhysics(double xForce, double yForce, double zForce, float delTime) {
	xVel += inertialMass * xForce * delTime;
	yVel += inertialMass * yForce * delTime;
	zVel += inertialMass * zForce * delTime;
}

void PhysicalObject::updatePosition(float delTime) {
	x += delTime * xVel;
	y += delTime * yVel;
	z += delTime * zVel;
}