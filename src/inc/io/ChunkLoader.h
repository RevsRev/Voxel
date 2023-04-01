#pragma once

#include <struc/Chunk.h>
#include <gen/WorldGenerator.h>
#include <string>
#include <struc/Voxel.h>
#include <phys/ChunkTypes.h>
#include <map>
#include <utility>
#include <mutex>
#include <map>
#include <set>
#include <iostream>
#include <util/data/Loader.h>

class ChunkLoader : public Loader<std::pair<long,long>,Chunk> {
private:

	bool chunkFileExists(long &chunkX, long &chunkY);
	Chunk* loadFromFile(long &chunkX, long &chunkY);
	void saveToFile(Chunk* &chunk);
	Chunk* generateChunk(long &chunkX, long &chunkY);
	Chunk* generateChunkLazy(long &chunkX, long &chunkY);

	void addToSurface(std::map<Triple<long, long, long>, Voxel>*& cachedVoxelSurface, long& colX, long& colY,
		unsigned char* thisColBitFlags,
		unsigned char* xMinusBitFlags,
		unsigned char* xPlusBitFlags,
		unsigned char* yMinusBitFlags,
		unsigned char* yPlusBitFlags);

	WorldGenerator* generator;
public:
	ChunkLoader(WorldGenerator* generator);
	~ChunkLoader();

	const static std::string CHUNK_FILE_DIR_PATH;
	Chunk* getChunk(long &chunkX, long &chunkY);
	//TODO - implement properly
	/*void removeChunk(long &chunkX, long &chunkY);*/
	
	Chunk& load(std::pair<long, long>& key, std::map<std::string, std::string>& args) override;

};