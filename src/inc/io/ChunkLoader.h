#pragma once

#include <struc/Chunk.h>
#include <gen/WorldGenerator.h>
#include <string>
#include <struc/Voxel.h>
#include <phys/ChunkTypes.h>
#include <map>
#include <utility>

class ChunkLoader {
private:

	std::map<std::pair<long, long>, Chunk*> chunkCache{};

	bool chunkFileExists(long chunkX, long chunkY);
	Chunk* loadFromFile(long chunkX, long chunkY);
	void saveToFile(Chunk* chunk);
	Chunk* generateChunk(long chunkX, long chunkY);
	void recacheNeighbours(long chunkX, long chunkY);
	void cacheNeighbour(int neighbour, Chunk* thisChunk, Chunk* thatChunk);

	WorldGenerator* generator;
public:
	ChunkLoader(WorldGenerator* generator);

	const static std::string CHUNK_FILE_DIR_PATH;
	Chunk* getChunk(long chunkX, long chunkY);
	void removeChunk(long chunkX, long chunkY);
	
};