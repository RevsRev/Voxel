#include "struc/Chunk.h"
#include <iostream>
#include <vector>

float cubeVerticesWithTex[] = {
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

//TODO - scaling for chunk size + prpoer coordinates
std::vector<float> getVerticesForVoxel(Voxel voxel, unsigned int i, unsigned int j, unsigned int k) {
	std::vector<float> retval{};
	int size = sizeof(cubeVerticesWithTex) / sizeof(float);
	for (int index = 0; index < size; index++) {
		switch (index % 5) {
		case 0:
			retval.push_back(i + cubeVerticesWithTex[index]);
			break;
		case 1:
			retval.push_back(j + cubeVerticesWithTex[index]);
			break;
		case 2:
			retval.push_back(k + cubeVerticesWithTex[index]);
			break;
		default:
			retval.push_back(cubeVerticesWithTex[index]);
		}
	}
	return retval;
}


std::vector<float>* Chunk::getVoxelPositionsToRender() {
	if (voxels == nullptr) {
		std::cout << "Null chunk data" << std::endl;
		return nullptr;
	}

	std::vector<float>* vecAllVertices = new std::vector<float>();

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				if (voxels[i][j][k].active
					&& isVoxelOnSurface(i,j,k)) {
					vecAllVertices->push_back((float)(chunkX + i));
					vecAllVertices->push_back((float)(chunkY + j));
					vecAllVertices->push_back((float)k);
				}
			}
		}
	}
	//std::cout << "Finished creating vertices for " << vecAllVertices->size() / (36*5) << " cubes" << std::endl;
	return vecAllVertices;

	//todo - extract 36 (num vertices for triangles) and 5 (num floats per vertex - 3 dim + 2 texture)
	/*float* arrVertices = new float[vecAllVertices.size()];
	for (int i = 0; i < vecAllVertices.size(); i++) {
		arrVertices[i] = vecAllVertices.at(i);
	}
	return arrVertices;*/

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