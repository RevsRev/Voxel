#include "struc/World.h"
#include <iostream>

World::World() {

	Voxel*** voxels = new Voxel * *[Chunk::CHUNK_SIZE];
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++) {
		voxels[i] = new Voxel * [Chunk::CHUNK_SIZE];
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++) {
			voxels[i][j] = new Voxel[Chunk::CHUNK_HEIGHT];
			for (int k = 0; k < Chunk::CHUNK_HEIGHT; k++) {
				Voxel vox = Voxel();
				if (i == 0 || i == Chunk::CHUNK_SIZE - 1
					|| j == 0 || j == Chunk::CHUNK_SIZE - 1
					|| k == 0 || k == Chunk::CHUNK_HEIGHT - 1)
				{
					vox.active = true;
				}

				vox.type = 1;
				voxels[i][j][k] = vox;
			}
		}
	}

	//For now, just have one simple chunk
	chunks = new Chunk*[1];
	chunks[0] = new Chunk[1];
	chunks[0][0] = Chunk(voxels);
}

std::vector<float>* World::getVoxelPositionsToRender() {

	//for now, just get from the only chunk in the world
	return chunks[0][0].getVoxelPositionsToRender();
}