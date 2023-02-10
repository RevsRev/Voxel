#include <io/ChunkLoader.h>

ChunkLoader::ChunkLoader(WorldGenerator* generator) {
	this->generator = generator;
}

bool ChunkLoader::chunkFileExists(long chunkX, long chunkY) {
	//TODO - Implement
	return false;
}

Chunk* ChunkLoader::loadFromFile(long chunkX, long chunkY) {
	//TODO - Implement
	return nullptr;
}

Chunk* ChunkLoader::generateChunk(long chunkX, long chunkY) {
	Voxel*** voxels = new Voxel * *[Chunk::CHUNK_SIZE];
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++) {
		voxels[i] = new Voxel * [Chunk::CHUNK_SIZE];
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++) {
			voxels[i][j] = new Voxel[Chunk::CHUNK_HEIGHT];
			float height = generator->generate(chunkX * Chunk::CHUNK_SIZE + i, chunkY * Chunk::CHUNK_SIZE + j);
			for (int k = 0; k < Chunk::CHUNK_HEIGHT; k++) {
				Voxel vox = Voxel();
				vox.type = ChunkType::DIRT;
				vox.active = k < height;
				voxels[i][j][k] = vox;
			}
		}
	}
	return new Chunk(voxels, Chunk::CHUNK_SIZE*chunkX, Chunk::CHUNK_SIZE*chunkY);
}

void ChunkLoader::saveToFile(Chunk* chunk) {
	//TODO - Implement
}

Chunk* ChunkLoader::getChunk(long chunkX, long chunkY) {
	Chunk* chunk;
	if (chunkFileExists(chunkX, chunkY)) {
		chunk = loadFromFile(chunkX, chunkY);
	}
	else {
		chunk = generateChunk(chunkX, chunkY);
		saveToFile(chunk);
	}
	chunkCache.insert({ std::pair<long, long>{chunkX, chunkY}, chunk });
	recacheNeighbours(chunkX, chunkY);
	return chunk;
}

void ChunkLoader::removeChunk(long chunkX, long chunkY) {
	Chunk* chunk = chunkCache.at(std::pair<long, long>{chunkX, chunkY});
	saveToFile(chunk);
	chunkCache.erase(std::pair<long, long>{chunkX, chunkY});
	delete chunk;
}

//TODO - This is a bit ugly... tidy up at some point.
void ChunkLoader::recacheNeighbours(long chunkX, long chunkY) {
	Chunk* thisChunk = getFromCache(std::pair<long, long>{chunkX, chunkY});

	Chunk* leftNeighbour = getFromCache(std::pair<long, long>{chunkX - 1, chunkY});
	Chunk* rightNeighbour = getFromCache(std::pair<long, long>{chunkX + 1, chunkY});
	Chunk* bottomNeighbour = getFromCache(std::pair<long, long>{chunkX, chunkY - 1});
	Chunk* topNeighbour = getFromCache(std::pair<long, long>{chunkX, chunkY + 1});

	cacheNeighbour(Chunk::X_MINUS, thisChunk, leftNeighbour);
	if (leftNeighbour != nullptr) {
		cacheNeighbour(Chunk::X_PLUS, leftNeighbour, thisChunk);
	}

	cacheNeighbour(Chunk::X_PLUS, thisChunk, rightNeighbour);
	if (rightNeighbour != nullptr) {
		cacheNeighbour(Chunk::X_MINUS, rightNeighbour, thisChunk);
	}

	cacheNeighbour(Chunk::Y_MINUS, thisChunk, bottomNeighbour);
	if (bottomNeighbour != nullptr) {
		cacheNeighbour(Chunk::Y_PLUS, bottomNeighbour, thisChunk);
	}

	cacheNeighbour(Chunk::Y_PLUS, thisChunk, topNeighbour);
	if (topNeighbour != nullptr) {
		cacheNeighbour(Chunk::Y_MINUS, topNeighbour, thisChunk);
	}
}

void ChunkLoader::cacheNeighbour(int neighbour, Chunk* thisChunk, Chunk* thatChunk) {
	thisChunk->setNeighbour(neighbour, thatChunk);
}

Chunk* ChunkLoader::getFromCache(std::pair<long, long> key) {
	if (chunkCache.find(key) == chunkCache.end()) {
		return nullptr;
	}
	return chunkCache.at(key);
}
