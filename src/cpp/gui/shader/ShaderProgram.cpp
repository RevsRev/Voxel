#include <gui/shader/ShaderProgram.h>

ShaderProgram::ShaderProgram() {
}

void ShaderProgram::addShader(Shader* shader) {
	shaders.push_back(shader);
}

void ShaderProgram::compile() {
	id = glCreateProgram();
	for (int i = 0; i < shaders.size(); i++) {
		glAttachShader(id, shaders.at(i)->getId());
	}
	
	glLinkProgram(id);

	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

int ShaderProgram::getUniformLocation(std::string uniformName) {
	return glGetUniformLocation(id, uniformName.c_str());
}

void ShaderProgram::use() {
	glUseProgram(id);
}

unsigned int ShaderProgram::getId() {
	return id;
}