#pragma once

#include "gui/draw/VBO.h"
#include "gui/draw/Attribute.h"
#include <vector>

class VAO {
private:
	unsigned int vao;
	std::vector<VBO*> vbos{};
public:

	VAO();
	~VAO();
	void bind();
	void addVBO(VBO* vbo);
};