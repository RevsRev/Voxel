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
	
	bool isVoxelOnSurface(unsigned int i, unsigned int j, unsigned int k);

	bool recache = true;
	float* cachedSurface = NULL;
	long cachedSurfaceSize;
	float* cachedVoxelColors = NULL;
	long cachedColorsSize;

	Voxel* getNeighbouringVoxel(int iNeighbour, int jNeighbour, int kNeighbour);

	void cacheVoxelData();
	std::pair<std::vector<float>*, std::vector<float>*> cacheSurfaceAndColors();
	std::pair<std::vector<float>*, std::vector<float>*> cacheSurfaceAndColorsLazy();
	std::pair<std::vector<float>*, std::vector<float>*> cacheSurfaceAndColorsIndustrious();

public:

	Chunk();
	Chunk(Voxel*** voxels, int chunkX, int chunkY);
	Chunk(std::map<Triple<long, long, long>, Voxel>* surface, int chunkX, int chunkY);
	~Chunk();
	void deleteVoxelArray();

	const static unsigned int CHUNK_SIZE = 64;
	const static unsigned int CHUNK_HEIGHT = 256;

	int getChunkX() const;
	int getChunkY() const;

	std::pair<long, float*> getVoxelPositionsToRender();
	std::pair<long, float*> getVoxelColorsToRender();

	void setCachedInfos(float* cachedSurface, long cachedSurfaceSize, float* cachedVoxelColors, long cachedColorsSize);
};