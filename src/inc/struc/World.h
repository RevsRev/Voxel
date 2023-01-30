#pragma once

#include "Chunk.h"
#include <vector>
#include <phys/ChunkTypes.h>

class World {
private:
	Chunk createChunk(int xChunkCoord, int yChunkCoord);

public:
	Chunk** chunks; //TODO - move back to private

	//width and depth measured in chunks
	const static unsigned int WORLD_WIDTH = 1;
	const static unsigned int WORLD_DEPTH = 1;

	std::vector<float>* getVoxelPositionsToRender();

	World();

};