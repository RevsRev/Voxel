#pragma once
#include "Voxel.h"
#include <vector>
#include <glm/vec3.hpp>
#include <phys/ChunkTypes.h>
#include <map>
#include <util/Triple.h>

extern float cubeVerticesWithNormalAndTex[];

class Chunk {
private:

	bool lazyInited = true;
	Voxel*** voxels;
	std::map<Triple<long, long, long>, Voxel>* cachedVoxelSurface;

	int chunkX;
	int chunkY;

	Chunk* neighbours[6]{nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

	//TODO - Chunk coordinates
	
	bool isVoxelOnSurface(unsigned int i, unsigned int j, unsigned int k);

	bool recache = true;
	float* cachedSurface = NULL;
	long cachedSurfaceSize;
	float* cachedVoxelColors = NULL;
	long cachedColorsSize;

	void cacheVoxelData();

public:

	Chunk();
	Chunk(Voxel*** voxels, int chunkX, int chunkY);
	Chunk(std::map<Triple<long, long, long>, Voxel>* surface, int chunkX, int chunkY);
	~Chunk();
	void Chunk::deleteVoxelArray();

	const static unsigned int CHUNK_SIZE = 16;
	const static unsigned int CHUNK_HEIGHT = 256;

	const static unsigned int TOP = 0;
	const static unsigned int BOTTOM = 1;
	const static unsigned int X_PLUS = 2;
	const static unsigned int X_MINUS = 3;
	const static unsigned int Y_PLUS = 4;
	const static unsigned int Y_MINUS = 5;

	std::pair<long, float*> getVoxelPositionsToRender();
	std::pair<long, float*> getVoxelColorsToRender();

	void setNeighbour(int neighbour, Chunk* chunk);

	//TODO - Add a destructor (otherwise will get memory leaks when the chunk loader deletes these)

};