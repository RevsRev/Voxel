#include <io/ChunkLoader.h>

ChunkLoader::ChunkLoader(WorldGenerator* generator) {
	this->generator = generator;
	initChunkLocks();
}
ChunkLoader::~ChunkLoader() {
	/*destroyChunkLocks();
	destroyChunks();*/

	//TODO - Not too bothered at the moment because this is only destroyed on application exit at the moment.
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
	std::mutex* chunkLock = getChunkLock(chunkX, chunkY);
	chunkLock->lock();

	Chunk* chunk;
	chunk = getFromCache(std::pair<long, long>{chunkX, chunkY});
	if (chunk != nullptr) {
		chunkLock->unlock();
		return chunk;
	}

	if (chunkFileExists(chunkX, chunkY)) {
		chunk = loadFromFile(chunkX, chunkY);
	}
	else {
		chunk = generateChunk(chunkX, chunkY);
		saveToFile(chunk);
	}
	chunkCache.insert({ std::pair<long, long>{chunkX, chunkY}, chunk });
	recacheNeighbours(chunkX, chunkY);

	chunkLock->unlock();

	return chunk;
}

void ChunkLoader::removeChunk(long chunkX, long chunkY) {
	std::mutex* chunkLock = getChunkLock(chunkX, chunkY);
	chunkLock->lock();

	Chunk* chunk = chunkCache.at(std::pair<long, long>{chunkX, chunkY});
	saveToFile(chunk);
	chunkCache.erase(std::pair<long, long>{chunkX, chunkY});
	delete chunk;

	chunkLock->unlock();
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

void ChunkLoader::initChunkLocks() {
	for (int i = 0; i < chunkLocksSize; i++) {
		for (int j = 0; j < chunkLocksSize; j++) {
			std::pair<long, long> key{ i,j };
			std::mutex* chunkLock = new std::mutex();
			chunkLocks.insert(std::pair < std::pair<long, long>, std::mutex*> { key, chunkLock });
		}
	}
}

//TODO - Make this more elegant (what happens if a lock is acquired while we delete? Although this scenario is unrealistic...)
void ChunkLoader::destroyChunkLocks() {
	for (int i = 0; i < chunkLocksSize; i++) {
		for (int j = 0; j < chunkLocksSize; j++) {
			std::pair<long, long> key{ i,j };
			std::mutex* chunkLock = chunkLocks.at(key);
			chunkLocks.erase(key);
			delete chunkLock;
		}
	}
}

std::mutex* ChunkLoader::getChunkLock(long chunkX, long chunkY) {
	long keyX = (chunkX % chunkLocksSize + chunkLocksSize) % chunkLocksSize;
	long keyY = (chunkY % chunkLocksSize + chunkLocksSize) % chunkLocksSize;

	std::pair<long, long> key{keyX, keyY };
	return chunkLocks.at(key);
}
