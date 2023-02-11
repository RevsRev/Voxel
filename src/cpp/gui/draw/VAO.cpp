#include "gui/draw/VAO.h"

#include <glad\glad.h>


VAO::VAO() {
	glGenVertexArrays(1, &vao);
}
VAO::~VAO() {
	for (int i = 0; i < vbos.size(); i++) {
		//delete vbos.at(i);
	}
}

void VAO::bind() {
	glBindVertexArray(vao);
}

void VAO::addVBO(VBO* vbo) {
	vbos.push_back(vbo);
	bind();
	vbo->bind();
}