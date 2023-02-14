#include "gui/shader/Shader.h"

Shader::Shader(const char* shaderCode, unsigned int &shaderType) {
	id = glCreateShader(shaderType);
	glShaderSource(id, 1, &shaderCode, NULL);
	compile();
}
void Shader::compile() {
	glCompileShader(id);
	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}
}

Shader* Shader::fromFile(const char* filePath, unsigned int shaderType) {
	std::string shaderCode;

	std::ifstream is;
	is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		is.open(filePath);
		std::stringstream buffer;
		buffer << is.rdbuf();
		is.close();
		shaderCode = buffer.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::FILE::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	return new Shader(shaderCode.c_str(), shaderType);
}

unsigned int Shader::getId() {
	return id;
}