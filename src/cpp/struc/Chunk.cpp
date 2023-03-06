#include "struc/Chunk.h"
#include <iostream>
#include <vector>
#include <struc/World.h>

float cubeVerticesWithNormalAndTex[] {
	//vertices (3), normal (3), texture (2)
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

//TODO - scaling for chunk size + prpoer coordinates
std::vector<float> getVerticesForVoxel(Voxel voxel, unsigned int i, unsigned int j, unsigned int k) {
	std::vector<float> retval{};
	int size = sizeof(cubeVerticesWithNormalAndTex) / sizeof(float);
	for (int index = 0; index < size; index++) {
		switch (index % 8) { //TODO - Really should to extract this.
		case 0:
			retval.push_back(i + cubeVerticesWithNormalAndTex[index]);
			break;
		case 1:
			retval.push_back(j + cubeVerticesWithNormalAndTex[index]);
			break;
		case 2:
			retval.push_back(k + cubeVerticesWithNormalAndTex[index]);
			break;
		default:
			retval.push_back(cubeVerticesWithNormalAndTex[index]);
		}
	}
	return retval;
}

bool Chunk::isVoxelOnSurface(unsigned int i, unsigned int j, unsigned int k) {

	Voxel* xMinusNeighbour = getNeighbouringVoxel(i - 1, j, k);
	Voxel* xPlusNeighbour = getNeighbouringVoxel(i + 1, j, k);
	Voxel* yMinusNeighbour = getNeighbouringVoxel(i, j - 1, k);
	Voxel* yPlusNeighbour = getNeighbouringVoxel(i, j + 1, k);
	Voxel* zMinusNeighbour = getNeighbouringVoxel(i, j, k - 1);
	Voxel* zPlusNeighbour = getNeighbouringVoxel(i, j, k + 1);

	bool activePlaneNeighbour = (xMinusNeighbour->active && xPlusNeighbour->active && yMinusNeighbour->active && yPlusNeighbour->active);
	if (!activePlaneNeighbour) {
		return true;
	}

	bool activeNeighbour = activePlaneNeighbour;
	if (zMinusNeighbour != nullptr) {
		activeNeighbour &= zMinusNeighbour->active;
	}
	if (zPlusNeighbour != nullptr) {
		activeNeighbour &= zPlusNeighbour->active;
	}
	return activeNeighbour;
}
Voxel* Chunk::getNeighbouringVoxel(int iNeighbour, int jNeighbour, int kNeighbour) {
	if (iNeighbour == -1
	  || iNeighbour == Chunk::CHUNK_SIZE + 1
	  || jNeighbour == -1
	  || jNeighbour == Chunk::CHUNK_SIZE + 1) {
		long x = chunkX + iNeighbour;
		long y = chunkY + jNeighbour;
		Voxel* retval = World::the()->getWorldGenerator()->generate(x, y);
		for (int k = 0; k < kNeighbour; k++) {
			retval = retval++;
		}
		return retval;
	}

	if (kNeighbour == -1 || kNeighbour == Chunk::CHUNK_HEIGHT + 1) {
		return nullptr; //TODO - Improve handling of k edges at some point?
	}

	return &voxels[iNeighbour][jNeighbour][kNeighbour];
}

void Chunk::cacheVoxelData() {
	if (!recache) {
		return;
	}

	std::pair<std::vector<float>*, std::vector<float>*> cachedSurfaceAndColors = cacheSurfaceAndColors();

	std::vector<float>* vecAllVertices = cachedSurfaceAndColors.first;
	std::vector<float>* vecAllColors = cachedSurfaceAndColors.second;

	delete[] cachedSurface;
	delete[] cachedVoxelColors;

	cachedColorsSize = vecAllColors->size();
	cachedSurfaceSize = vecAllVertices->size();

	cachedVoxelColors = new float[cachedColorsSize];
	cachedSurface = new float[cachedSurfaceSize];

	long loopSize = vecAllVertices->size();

	for (int i = 0; i < loopSize; i++) {
		cachedSurface[i] = vecAllVertices->at(i);
		cachedVoxelColors[i] = vecAllColors->at(i);
	}
	delete vecAllVertices;
	delete vecAllColors;

	recache = false;
}

std::pair<std::vector<float>*, std::vector<float>*> Chunk::cacheSurfaceAndColors() {
	if (lazyInited) {
		return cacheSurfaceAndColorsLazy();
	}
	return cacheSurfaceAndColorsIndustrious();
}
std::pair<std::vector<float>*, std::vector<float>*> Chunk::cacheSurfaceAndColorsLazy() {
	std::vector<float>* vecAllVertices = new std::vector<float>();
	std::vector<float>* vecAllColors = new std::vector<float>();

	for (auto it = cachedVoxelSurface->begin(); it != cachedVoxelSurface->end(); it++) {
		Triple<long, long, long> key = (*it).first;
		Voxel vox = (*it).second;
		vecAllVertices->push_back((float)key.first);
		vecAllVertices->push_back((float)key.second);
		vecAllVertices->push_back((float)key.third);

		glm::vec3* color = ChunkType::getColor(vox.type);
		vecAllColors->push_back(color->x);
		vecAllColors->push_back(color->y);
		vecAllColors->push_back(color->z);
		delete color;
	}
	return std::pair<std::vector<float>*, std::vector<float>*>{vecAllVertices, vecAllColors};
}
std::pair<std::vector<float>*, std::vector<float>*> Chunk::cacheSurfaceAndColorsIndustrious() {
	std::vector<float>* vecAllVertices = new std::vector<float>();
	std::vector<float>* vecAllColors = new std::vector<float>();

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				if (voxels[i][j][k].active
					&& isVoxelOnSurface(i, j, k)) {
					vecAllVertices->push_back((float)(chunkX + i));
					vecAllVertices->push_back((float)(chunkY + j));
					vecAllVertices->push_back((float)k);

					glm::vec3* color = ChunkType::getColor(voxels[i][j][k].type);
					vecAllColors->push_back(color->x);
					vecAllColors->push_back(color->y);
					vecAllColors->push_back(color->z);
					delete color;
				}
			}
		}
	}
	return std::pair<std::vector<float>*, std::vector<float>*>{vecAllVertices, vecAllColors};
}

std::pair<long, float*> Chunk::getVoxelPositionsToRender() {
	cacheVoxelData();
	return std::pair<long,float*>{cachedSurfaceSize, cachedSurface};
}
std::pair<long, float*> Chunk::getVoxelColorsToRender() {
	cacheVoxelData();
	return std::pair<long, float*>{cachedColorsSize, cachedVoxelColors};
}

void Chunk::setCachedInfos(float* cachedSurface, long cachedSurfaceSize, float* cachedVoxelColors, long cachedColorsSize) {
	this->cachedColorsSize = cachedColorsSize;
	this->cachedVoxelColors = cachedVoxelColors;
	this->cachedSurfaceSize = cachedSurfaceSize;
	this->cachedSurface = cachedSurface;
	this->recache = false;
}

//default constructor used when initizlizing arrays!
Chunk::Chunk() {
}
Chunk::Chunk(Voxel*** voxels, int chunkX, int chunkY) {
	this->voxels = voxels;
	this->chunkX = chunkX;
	this->chunkY = chunkY;

	lazyInited = false;
}
Chunk::Chunk(std::map<Triple<long, long, long>, Voxel>* surface, int chunkX, int chunkY) {
	this->cachedVoxelSurface = surface;
	this->chunkX = chunkX;
	this->chunkY = chunkY;

	lazyInited = true;

	cacheVoxelData();
}
Chunk::~Chunk() {
	if (lazyInited) {
		delete cachedVoxelSurface;
	}
	else {
		deleteVoxelArray();
	}
	
	delete[] cachedSurface;
	delete[] cachedVoxelColors;
}
void Chunk::deleteVoxelArray() {
	for (int i = 0; i < CHUNK_SIZE; i++) {
		Voxel** yzSlize = voxels[i];
		for (int j = 0; j < CHUNK_SIZE; j++) {
			delete[] yzSlize[j];
		}
		delete[] yzSlize;
	}
	delete[] voxels;
}

int Chunk::getChunkX() { return chunkX; }
int Chunk::getChunkY() { return chunkY; }