#pragma once

#include <struc/Chunk.h>
#include <gen/WorldGenerator.h>
#include <string>
#include <struc/Voxel.h>
#include <phys/ChunkTypes.h>
#include <map>
#include <utility>
#include <mutex>

class ChunkLoader {
private:

	long chunkLocksSize = 10;

	std::map<std::pair<long, long>, Chunk*> chunkCache{};
	std::map<std::pair<long, long>, std::mutex*> chunkLocks{};

	bool chunkFileExists(long chunkX, long chunkY);
	Chunk* loadFromFile(long chunkX, long chunkY);
	void saveToFile(Chunk* chunk);
	Chunk* generateChunk(long chunkX, long chunkY);
	void recacheNeighbours(long chunkX, long chunkY);
	void cacheNeighbour(int neighbour, Chunk* thisChunk, Chunk* thatChunk);
	Chunk* getFromCache(std::pair<long, long> key);

	void initChunkLocks();
	void destroyChunkLocks();
	std::mutex* getChunkLock(long chunkX, long chunkY);

	WorldGenerator* generator;
public:
	ChunkLoader(WorldGenerator* generator);
	~ChunkLoader();

	const static std::string CHUNK_FILE_DIR_PATH;
	Chunk* getChunk(long chunkX, long chunkY);
	void removeChunk(long chunkX, long chunkY);
	
};