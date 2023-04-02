#pragma once

#include "struc/Chunk.h"
#include "gui/draw/VAO.h"
#include "gui/shader/ShaderProgram.h"


class ChunkRenderer {
private:
	//thing being rendered
	Chunk* chunk;

	bool recache = true;
	int numTrianglesForArray;

	//for rendering
	VAO vao;
	VBO vboCube;
	VBO vboPositionAndColorInstance;
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
	void setChunk(Chunk* chunk);
	void render();
	ShaderProgram* getShaderProgram();
};