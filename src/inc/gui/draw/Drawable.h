#pragma once

#include "gui/draw/VAO.h"
#include "gui/shader/ShaderProgram.h"

class Drawable {
public:
	VAO* vao;
	ShaderProgram* shaderProgram;

	virtual void draw() = 0;
};

class VoxelDrawable : private Drawable {
public:
	VoxelDrawable();
	void draw();
private:
	void createShaderProgram();
};