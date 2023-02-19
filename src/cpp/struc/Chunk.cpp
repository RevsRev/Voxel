#include "struc/Chunk.h"
#include <iostream>
#include <vector>

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
		switch (index % 8) { //TODO - Really need to extract this.
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


void Chunk::cacheVoxelData() {
	if (!recache) {
		return;
	}
	//std::cout << "Caching Voxel Data for chunk (x,y) = (" << chunkX << "," << chunkY << ")" << std::endl;

	if (voxels == nullptr) {
		std::cout << "Null chunk data" << std::endl;
		return;
	}

	std::vector<float>* vecAllVertices = new std::vector<float>();
	std::vector<float>* vecAllColors = new std::vector<float>();

	//TODO - Refactor
	if (lazyInited) {
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
	}
	else {
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
	}
	

	delete[] cachedSurface;
	int size = vecAllVertices->size();
	cachedSurface = new float[size];
	for (int i = 0; i < size; i++) {
		cachedSurface[i] = vecAllVertices->at(i);
	}
	delete vecAllVertices;
	cachedSurfaceSize = size;


	delete[] cachedVoxelColors;
	size = vecAllColors->size();
	cachedVoxelColors = new float[size];
	for (int i = 0; i < size; i++) {
		cachedVoxelColors[i] = vecAllColors->at(i);
	}
	delete vecAllColors;
	cachedColorsSize = size;

	recache = false;
}

std::pair<long, float*> Chunk::getVoxelPositionsToRender() {
	cacheVoxelData();
	return std::pair<long,float*>{cachedSurfaceSize, cachedSurface};
}
std::pair<long, float*> Chunk::getVoxelColorsToRender() {
	cacheVoxelData();
	return std::pair<long, float*>{cachedColorsSize, cachedVoxelColors};
}

bool Chunk::isVoxelOnSurface(unsigned int i, unsigned int j, unsigned int k) {
	if (i == 0) {
		if (neighbours[X_MINUS] == nullptr) {
			return true;
		}
		else {
			if (!neighbours[X_MINUS]->voxels[Chunk::CHUNK_SIZE-1][j][k].active) {
				return true;
			}
		}
	}
	else {
		if (!voxels[i-1][j][k].active) {
			return true;
		}
	}

	if (i == Chunk::CHUNK_SIZE-1) {
		if (neighbours[X_PLUS] == nullptr) {
			return true;
		}
		else {
			if (!neighbours[X_PLUS]->voxels[0][j][k].active) {
				return true;
			}
		}
	}
	else {
		if (!voxels[i+1][j][k].active) {
			return true;
		}
	}

	if (j == 0) {
		if (neighbours[Y_MINUS] == nullptr) {
			return true;
		}
		else {
			if (!neighbours[Y_MINUS]->voxels[i][Chunk::CHUNK_SIZE - 1][k].active) {
				return true;
			}
		}
	}
	else {
		if (!voxels[i][j-1][k].active) {
			return true;
		}
	}

	if (j == Chunk::CHUNK_SIZE - 1) {
		if (neighbours[Y_PLUS] == nullptr) {
			return true;
		}
		else {
			if (!neighbours[Y_PLUS]->voxels[i][0][k].active) {
				return true;
			}
		}
	}
	else {
		if (!voxels[i][j+1][k].active) {
			return true;
		}
	}

	if (k == 0) {
		if (neighbours[BOTTOM] == nullptr) {
			return true;
		}
		else {
			if (!neighbours[BOTTOM]->voxels[i][j][Chunk::CHUNK_HEIGHT-1].active) {
				return true;
			}
		}
	}
	else {
		if (!voxels[i][j][k-1].active) {
			return true;
		}
	}

	if (k == Chunk::CHUNK_HEIGHT - 1) {
		if (neighbours[TOP] == nullptr) {
			return true;
		}
		else {
			if (!neighbours[TOP]->voxels[i][j][0].active) {
				return true;
			}
		}
	}
	else {
		if (!voxels[i][j][k+1].active) {
			return true;
		}
	}

	//TODO - This method is gross. Need to refactor.
	return false;
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

void Chunk::setNeighbour(int neighbour, Chunk* chunk) {
	neighbours[neighbour] = chunk;
}