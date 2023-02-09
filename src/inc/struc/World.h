#pragma once

#include "Chunk.h"
#include <vector>
#include <phys/ChunkTypes.h>
#include <gen/WorldGenerator.h>
#include <gen/perlin/PerlinMountain.h>
#include <io/ChunkLoader.h>

class World {
private:
	long seed = 5; //TODO -Extract at some point
	WorldGenerator generator{ seed };
	ChunkLoader loader{ &generator };

	void initGenerator();
	Chunk createChunk(int xChunkCoord, int yChunkCoord);

	World();

public:
	Chunk** chunks; //TODO - move back to private

	static World* the();

	//width and depth measured in chunks
	const static unsigned int WORLD_WIDTH = 1;
	const static unsigned int WORLD_DEPTH = 1;

	std::vector<float>* getVoxelPositionsToRender();
	ChunkLoader* getChunkLoader();
};