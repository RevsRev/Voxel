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

	if (voxels == nullptr) {
		std::cout << "Null chunk data" << std::endl;
		return;
	}

	std::vector<float>* vecAllVertices = new std::vector<float>();
	std::vector<float>* vecAllColors = new std::vector<float>();

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				if (voxels[i][j][k].active
					&& isVoxelOnSurface(i,j,k)) {
					vecAllVertices->push_back((float)(chunkX + i));
					vecAllVertices->push_back((float)(chunkY + j));
					vecAllVertices->push_back((float)k);

					glm::vec3* color = ChunkType::getColor(voxels[i][j][k].type);
					vecAllColors->push_back(color->x);
					vecAllColors->push_back(color->y);
					vecAllColors->push_back(color->z);
				}
			}
		}
	}

	cachedSurface = vecAllVertices;
	cachedVoxelColors = vecAllColors;
	recache = false;
}

std::vector<float>* Chunk::getVoxelPositionsToRender() {
	cacheVoxelData();
	return cachedSurface;
}
std::vector<float>* Chunk::getVoxelColorsToRender() {
	cacheVoxelData();
	return cachedVoxelColors;
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

//default constructor used when initizlizing arrays!
Chunk::Chunk() {
}
Chunk::Chunk(Voxel*** voxels, int chunkX, int chunkY) {
	this->voxels = voxels;
	this->chunkX = chunkX;
	this->chunkY = chunkY;
}

void Chunk::setNeighbour(int neighbour, Chunk* chunk) {
	neighbours[neighbour] = chunk;
}