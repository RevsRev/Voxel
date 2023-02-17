#include "gui/draw/VAO.h"

#include <glad\glad.h>


VAO::VAO() {
}
VAO::~VAO() {
	bind();
	for (int i = 0; i < vbos.size(); i++) {
		delete vbos.at(i);
	}

	if (initialized) {
		glDeleteVertexArrays(1, &vao);
	}
}

void VAO::init() {
	glGenVertexArrays(1, &vao);
	initialized = true;
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
	bind();
	thisVbo->bind();
}