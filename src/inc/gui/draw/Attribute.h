#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Attribute {
private:

	//necessary for creating the pointer
	unsigned int location;
	unsigned int length;
	GLenum dataType;
	GLboolean normalized;
	GLsizei stride;
	void* offset;

	//other properties
	unsigned int divisor = 0;

public:
	Attribute();
	Attribute(unsigned int location, unsigned int length, GLenum dataType, GLboolean normalized, GLsizei stride, void* offset);
	void createVertexAttribPointer();
	void enable();
	void setDivisor(unsigned int divisor);
};