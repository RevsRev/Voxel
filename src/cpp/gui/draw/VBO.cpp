#include "gui/draw/VBO.h"

#include <glad\glad.h>

VBO::VBO() {
	//just for object initialization
	//TODO - Find a better solution at some point
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

VBO::VBO(float* vertexData, unsigned int vertexDataLength) {
	glGenBuffers(1, &vbo);
	setBufferData(vertexData, vertexDataLength);
}

void VBO::setBufferData(float* vertexData, unsigned int vertexDataLength) {
	this->vertexData = vertexData;
	this->vertexDataLength = vertexDataLength;
	bind();
	glBufferData(GL_ARRAY_BUFFER, vertexDataLength, vertexData, GL_STATIC_DRAW);
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::addAttribute(Attribute* attribute) {
	attributes.push_back(attribute);
	bind();
	attribute->createVertexAttribPointer();
	attribute->enable();
}