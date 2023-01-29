#include "struc/World.h"
#include <iostream>
#include "gen/PerlinNoise.h"

World::World() {

	//TODO - extract elsewhere. Get rid of magic numbers
	int chunkXRange = 10;
	int chunkYRange = 10;

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

Chunk World::createChunk(int xChunkCoord, int yChunkCoord) {

	PerlinNoise noise{ 5, 30, 50 };
	int x = Chunk::CHUNK_SIZE * xChunkCoord;
	int y = Chunk::CHUNK_SIZE * yChunkCoord;

	Voxel*** voxels = new Voxel * *[Chunk::CHUNK_SIZE];
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++) {
		voxels[i] = new Voxel * [Chunk::CHUNK_SIZE];
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++) {
			voxels[i][j] = new Voxel[Chunk::CHUNK_HEIGHT];
			float height = noise.compute(x + i, y + j);
			for (int k = 0; k < Chunk::CHUNK_HEIGHT; k++) {
				Voxel vox = Voxel();
				vox.active = k < height;
				vox.type = 1;
				voxels[i][j][k] = vox;
			}
		}
	}

	return Chunk(voxels, x, y);
}


std::vector<float>* World::getVoxelPositionsToRender() {

	std::vector<float>* voxelPositions = new std::vector<float>();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::vector<float>* positions = chunks[i][j].getVoxelPositionsToRender();
			voxelPositions->insert(voxelPositions->end(), positions->begin(), positions->end());
		}
	}
	return voxelPositions;
}