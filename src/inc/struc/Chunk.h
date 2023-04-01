#pragma once
#include "Voxel.h"
#include <vector>
#include <glm/vec3.hpp>
#include <phys/ChunkTypes.h>
#include <map>
#include <util/Triple.h>
#include <vector>

extern float cubeVerticesWithNormalAndTex[];

class Chunk {
private:

	bool lazyInited = true;
	Voxel*** voxels;
	std::map<Triple<long, long, long>, Voxel>* cachedVoxelSurface;
	std::vector<float> cachedFloatSurface{};
	std::vector<float> cachedFloatColors{};

	int chunkX;
	int chunkY;
	
	bool isVoxelOnSurface(unsigned int i, unsigned int j, unsigned int k);

	bool recache = true;

	Voxel* getNeighbouringVoxel(int iNeighbour, int jNeighbour, int kNeighbour);

	void cacheSurfaceAndColors();
	void cacheSurfaceAndColorsLazy();
	void cacheSurfaceAndColorsIndustrious();

public:

	Chunk();
	Chunk(Voxel*** voxels, int chunkX, int chunkY);
	Chunk(std::map<Triple<long, long, long>, Voxel>* surface, int chunkX, int chunkY);
	~Chunk();
	void deleteVoxelArray();

	const static unsigned int CHUNK_SIZE = 16;
	const static unsigned int CHUNK_HEIGHT = 256;

	int getChunkX() const;
	int getChunkY() const;

	void cacheVoxelData();
	std::pair<long, float*> getVoxelPositionsToRender();
	std::pair<long, float*> getVoxelColorsToRender();
};