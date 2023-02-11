#pragma once

#include "gui/draw/Attribute.h"
#include <vector>

class VBO {
private:
	unsigned int vbo;

	float* vertexData = NULL;
	unsigned int vertexDataLength;

	std::vector<Attribute*> attributes;

public:
	VBO();
	VBO(float* vertexData, unsigned int vertexDataLength);
	~VBO();

	void bind();
	void setBufferData(float* vertexData, unsigned int vertexDataLength);
	void addAttribute(Attribute* attribute);
};
