#include "gui/draw/Drawable.h"

VoxelDrawable::VoxelDrawable() {
	createShaderProgram();
}

void VoxelDrawable::draw() {
	shaderProgram->use();
	vao->bind();
}

void VoxelDrawable::createShaderProgram() {
	std::string fragShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\fragment\\voxel.txt";
	std::string vertexShaderPath = "C:\\Users\\eddie\\Documents\\Voxel\\Voxel\\resource\\shader\\vertex\\voxel.txt";
	Shader* fragShader = Shader::fromFile(fragShaderPath.c_str(), GL_FRAGMENT_SHADER);
	Shader* vertexShader = Shader::fromFile(vertexShaderPath.c_str(), GL_VERTEX_SHADER);
	shaderProgram = new ShaderProgram();
	shaderProgram->addShader(fragShader);
	shaderProgram->addShader(vertexShader);
	shaderProgram->compile();
}