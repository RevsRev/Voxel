#pragma once

#include "gui/draw/Attribute.h"
#include <vector>

class VBO {
private:
	unsigned int vbo;// = NULL;
	bool initialized = false;

	float* vertexData = NULL;
	unsigned int vertexDataLength;

	std::vector<Attribute*> attributes;

public:
	VBO();
	VBO(float* vertexData, unsigned int vertexDataLength);
	~VBO();

	void init();
	void bind();
	void setBufferData(float* vertexData, unsigned int vertexDataLength);
	void addAttribute(Attribute* attribute);
};
