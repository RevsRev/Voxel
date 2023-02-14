#include <gui/shader/ShaderProgram.h>

ShaderProgram::ShaderProgram() {
}

ShaderProgram::~ShaderProgram() {
	for (int i = shaders.size() -1; i > 0; i--) {
		delete shaders.at(i);
	}

	if (compiled)
	{
		glDeleteProgram(id);
	}
}

void ShaderProgram::addShader(Shader* shader) {
	shaders.push_back(new Shader(*shader));
}

void ShaderProgram::compile() {
	id = glCreateProgram();
	compiled = true;
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