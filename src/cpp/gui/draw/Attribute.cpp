#include "gui/draw/Attribute.h"

Attribute::Attribute() {
	//just for array initialization
	//TODO - find a better solution at some point
}

Attribute::Attribute(unsigned int location, unsigned int length, GLenum dataType, GLboolean normalized, GLsizei stride, void* offset) {
	this->location = location;
	this->length = length;
	this->dataType = dataType;
	this->normalized = normalized;
	this->stride = stride;
	this->offset = offset;
}

Attribute::~Attribute() {
	//delete offset;
}

void Attribute::createVertexAttribPointer() {
	glVertexAttribPointer(location, length, dataType, normalized, stride, offset);
}

void Attribute::enable() {
	glEnableVertexAttribArray(location);
	glVertexAttribDivisor(location, divisor);
}

void Attribute::setDivisor(unsigned int divisor) {
	this->divisor = divisor;
}