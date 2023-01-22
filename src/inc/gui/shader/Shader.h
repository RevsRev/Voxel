#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>

class Shader {
private:
	unsigned int id;
	Shader(const char* shaderCode, unsigned int &shaderType);
	void compile();
public:
	static Shader* fromFile(const char* filePath, unsigned int shaderType);
	unsigned int getId();
};