#pragma once
#include "Voxel.h"
#include <vector>

extern float cubeVerticesWithTex[];

class Chunk {
private:
	Voxel*** voxels;

	int chunkX;
	int chunkY;

	Chunk* neighbours[6]{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	//TODO - Chunk coordinates
	
	bool isVoxelOnSurface(unsigned int i, unsigned int j, unsigned int k);

public:

	Chunk();
	Chunk(Voxel*** voxels, int chunkX, int chunkY);

	const static unsigned int CHUNK_SIZE = 16;
	const static unsigned int CHUNK_HEIGHT = 256;

	const static unsigned int TOP = 0;
	const static unsigned int BOTTOM = 1;
	const static unsigned int X_PLUS = 2;
	const static unsigned int X_MINUS = 3;
	const static unsigned int Y_PLUS = 4;
	const static unsigned int Y_MINUS = 5;

	//TODO - DO this properly at some point!
	std::vector<float>* getVoxelPositionsToRender();

	void setNeighbour(int neighbour, Chunk* chunk);

};