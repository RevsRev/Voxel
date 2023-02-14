#pragma once

#include "Shader.h"
#include <vector>
#include <string>

class ShaderProgram {
private:
	unsigned int id;
	bool compiled = false;
	std::vector<Shader*> shaders{};
public:
	ShaderProgram();
	~ShaderProgram();
	unsigned int getId();
	void addShader(Shader* shader);
	void compile();
	void use();

	int getUniformLocation(std::string uniformName);
};