#include "gui/draw/VAO.h"

#include <glad\glad.h>


VAO::VAO() {
	glGenVertexArrays(1, &vao);
}

void VAO::bind() {
	glBindVertexArray(vao);
}

void VAO::addVBO(VBO* vbo) {
	vbos.push_back(vbo);
	bind();
	vbo->bind();
}