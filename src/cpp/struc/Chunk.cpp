#include "struc/Chunk.h"
#include <iostream>
#include <vector>

static float cubeVerticesWithTex[] = {
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


std::vector<float>* Chunk::getVerticesToRender() {
	if (voxels == nullptr) {
		std::cout << "Null chunk data" << std::endl;
		return nullptr;
	}

	std::vector<float>* vecAllVertices = new std::vector<float>();

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				if (voxels[i][j][k].active) {
					std::vector<float> voxelVertices = getVerticesForVoxel(voxels[i][j][k], i, j, k);
					vecAllVertices->reserve(vecAllVertices->size() + voxelVertices.size());
					vecAllVertices->insert(vecAllVertices->end(), voxelVertices.begin(), voxelVertices.end());
				}
			}
		}
	}
	std::cout << "Finished creating vertices for " << vecAllVertices->size() / (36*5) << " cubes" << std::endl;
	return vecAllVertices;

	//todo - extract 36 (num vertices for triangles) and 5 (num floats per vertex - 3 dim + 2 texture)
	/*float* arrVertices = new float[vecAllVertices.size()];
	for (int i = 0; i < vecAllVertices.size(); i++) {
		arrVertices[i] = vecAllVertices.at(i);
	}
	return arrVertices;*/

}

//default constructor used when initizlizing arrays!
Chunk::Chunk() {
}
Chunk::Chunk(Voxel*** voxels) {
	this->voxels = voxels;
}