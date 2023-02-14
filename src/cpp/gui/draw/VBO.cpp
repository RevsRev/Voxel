#include "gui/draw/VBO.h"

#include <glad\glad.h>

VBO::VBO() {
}

VBO::VBO(float* vertexData, unsigned int vertexDataLength) {
	this->vertexData = vertexData;
	this->vertexDataLength = vertexDataLength;
}

VBO::~VBO() {
	//delete[] vertexData;
	for (int i = 0; i < attributes.size(); i++) {
		delete attributes.at(i);
	}

	if (initialized) {
		glDeleteBuffers(1, &vbo);
	}
}

void VBO::init() {
	glGenBuffers(1, &vbo);
	initialized = true;
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
	Attribute* thisAttribute = new Attribute(*attribute);
	attributes.push_back(thisAttribute);
	bind();
	thisAttribute->createVertexAttribPointer();
	thisAttribute->enable();
}