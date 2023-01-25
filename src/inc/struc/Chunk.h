#pragma once
#include "Voxel.h"
#include <vector>

extern float cubeVerticesWithTex[];

class Chunk {
private:
	Voxel*** voxels;

	int chunkX;
	int chunkY;

	//TODO - Chunk coordinates

public:

	Chunk();
	Chunk(Voxel*** voxels, int chunkX, int chunkY);

	const static unsigned int CHUNK_SIZE = 16;
	const static unsigned int CHUNK_HEIGHT = 256;

	//TODO - DO this properly at some point!
	std::vector<float>* getVoxelPositionsToRender();

};