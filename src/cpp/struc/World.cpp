#include "struc/World.h"
#include <iostream>
#include "gen/perlin/PerlinNoise.h"

World* World::the() {
	static World* theWindow = new World();
	return theWindow;
}

World::World() {

	initGenerator();

	//TODO - extract elsewhere. Get rid of magic numbers
	int chunkXRange = 20;
	int chunkYRange = 20;

	chunks = new Chunk * [chunkXRange];

	for (int i = 0; i < chunkXRange; i++) {
		chunks[i] = new Chunk[chunkYRange];
		for (int j = 0; j < chunkYRange; j++) {
			chunks[i][j] = createChunk(i, j);
		}
	}

	//Now cache neighbours
	for (int i = 0; i < chunkXRange; i++) {
		for (int j = 0; j < chunkYRange; j++) {
			Chunk* chunk = &chunks[i][j];
			if (i != 0) {
				chunk->setNeighbour(Chunk::X_MINUS, &chunks[i - 1][j]);
			}

			if (i != chunkXRange - 1) {
				chunk->setNeighbour(Chunk::X_PLUS, &chunks[i + 1][j]);
			}

			if (j != 0) {
				chunk->setNeighbour(Chunk::Y_MINUS, &chunks[i][j - 1]);
			}

			if (j != chunkYRange - 1) {
				chunk->setNeighbour(Chunk::Y_PLUS, &chunks[i][j + 1]);
			}
		}
	}
}

void World::initGenerator() {
	unsigned int resolution = 30;
	unsigned int height = 50;
	PerlinMountain* mountain = new PerlinMountain(seed, resolution, height);
	PerlinMountain* moreMountain = new PerlinMountain(seed, 78, 100);
	generator.addPostProcessor(mountain);
	generator.addPostProcessor(moreMountain);
}

Chunk World::createChunk(int xChunkCoord, int yChunkCoord) {

	long seed = 5;
	unsigned int resolution = 30;
	unsigned int height = 50;
	WorldGenerator generator{ seed };
	PerlinMountain* mountain = new PerlinMountain(seed, resolution, height);
	PerlinMountain* moreMountain = new PerlinMountain(seed, 78, 100);
	generator.addPostProcessor(mountain);
	generator.addPostProcessor(moreMountain);

	int x = Chunk::CHUNK_SIZE * xChunkCoord;
	int y = Chunk::CHUNK_SIZE * yChunkCoord;

	Voxel*** voxels = new Voxel * *[Chunk::CHUNK_SIZE];
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++) {
		voxels[i] = new Voxel * [Chunk::CHUNK_SIZE];
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++) {
			voxels[i][j] = new Voxel[Chunk::CHUNK_HEIGHT];
			float height = generator.generate(x + i, y + j);
			for (int k = 0; k < Chunk::CHUNK_HEIGHT; k++) {
				Voxel vox = Voxel();
				vox.active = k < height;
				vox.type = ChunkType::CHUNK_TYPES::DIRT;
				voxels[i][j][k] = vox;
			}
		}
	}

	return Chunk(voxels, x, y);
}

ChunkLoader* World::getChunkLoader() {
	return &loader;
}

std::vector<float>* World::getVoxelPositionsToRender() {

	std::vector<float>* voxelPositions = new std::vector<float>();

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			std::vector<float>* positions = chunks[i][j].getVoxelPositionsToRender();
			voxelPositions->insert(voxelPositions->end(), positions->begin(), positions->end());
		}
	}
	return voxelPositions;
}