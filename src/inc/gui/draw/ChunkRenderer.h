#pragma once

#include "struc/Chunk.h"
#include "gui/draw/VAO.h"
#include "gui/shader/ShaderProgram.h"


class ChunkRenderer {
private:
	//thing being rendered
	Chunk* chunk;

	//for rendering
	VAO vao;
	VBO vboCube;
	VBO vboPositionInstance;
	VBO vboColorInstance;
	Attribute attributeVertex;
	Attribute attributeTexture;
	Attribute attributeInstance;
	
	ShaderProgram shaderProgram;

	void init();
	void initVao();
	void initShaderProgram();
public:
	ChunkRenderer(Chunk* chunk);
	//~ChunkRenderer();
	void render();
	ShaderProgram* getShaderProgram();
};