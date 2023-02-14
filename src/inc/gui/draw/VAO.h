#pragma once

#include "gui/draw/VBO.h"
#include "gui/draw/Attribute.h"
#include <vector>

class VAO {
private:
	unsigned int vao;
	bool initialized = false;
	std::vector<VBO*> vbos{};
public:

	VAO();
	~VAO();

	void init();
	void bind();
	void addVBO(VBO* vbo);
};