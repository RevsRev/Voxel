#include "gui/draw/VBO.h"

VBO::VBO() {
}

VBO::VBO(float* vertexData, unsigned int vertexDataLength) {
	this->vertexData = vertexData;
	this->vertexDataLength = vertexDataLength;
}

VBO::~VBO() {
	//delete[] vertexData;
	GlLock::lock();

	for (int i = 0; i < attributes.size(); i++) {
		delete attributes.at(i);
	}

	if (initialized) {
		glDeleteBuffers(1, &vbo);
	}
	GlLock::unlock();
}

void VBO::init() {
	GlLock::lock();
	glGenBuffers(1, &vbo);
	initialized = true;
	GlLock::unlock();
}

void VBO::setBufferData(float* vertexData, unsigned int vertexDataLength) {
	this->vertexData = vertexData;
	this->vertexDataLength = vertexDataLength;
	GlLock::lock();
	bind();
	glBufferData(GL_ARRAY_BUFFER, vertexDataLength, vertexData, GL_STATIC_DRAW);
	GlLock::unlock();
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::addAttribute(Attribute* attribute) {
	Attribute* thisAttribute = new Attribute(*attribute);
	attributes.push_back(thisAttribute);
	GlLock::lock();
	bind();
	thisAttribute->createVertexAttribPointer();
	thisAttribute->enable();
	GlLock::unlock();
}