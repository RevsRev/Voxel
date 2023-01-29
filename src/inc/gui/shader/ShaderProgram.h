#pragma once

#include "Shader.h"
#include <vector>
#include <string>

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

	int getUniformLocation(std::string uniformName);
};