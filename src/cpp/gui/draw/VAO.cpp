#include "gui/draw/VAO.h"

VAO::VAO() {
}
VAO::~VAO() {

	GlLock::lock();

	bind();
	for (int i = 0; i < vbos.size(); i++) {
		delete vbos.at(i);
	}

	if (initialized) {
		glDeleteVertexArrays(1, &vao);
	}

	GlLock::unlock();
}

void VAO::init() {
	GlLock::lock();
	glGenVertexArrays(1, &vao);
	initialized = true;
	GlLock::unlock();
}

void VAO::bind() {
	if (initialized) {
		glBindVertexArray(vao);
	}
}

void VAO::addVBO(VBO* vbo) 
{	
	VBO* thisVbo = new VBO(*vbo);
	vbos.push_back(thisVbo);
	GlLock::lock();
	bind();
	thisVbo->bind();
	GlLock::unlock();
}