#pragma once

#include "Shader.h"
#include <vector>

class ShaderProgram {
private:
	unsigned int id;
	std::vector<Shader*> shaders{};
public:
	ShaderProgram();
	unsigned int getId();
	void addShader(Shader* shader);
	void compile();
	void use();
};