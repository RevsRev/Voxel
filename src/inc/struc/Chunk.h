#pragma once
#include "Voxel.h"
#include <vector>

class Chunk {
private:
	Voxel*** voxels;

	//TODO - Chunk coordinates

public:

	Chunk();
	Chunk(Voxel*** voxels);

	const static unsigned int CHUNK_SIZE = 16;
	const static unsigned int CHUNK_HEIGHT = 64;

	//TODO - DO this properly at some point!
	std::vector<float>* getVerticesToRender();

};