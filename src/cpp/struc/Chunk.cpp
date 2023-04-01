#include "struc/Chunk.h"
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
	cacheSurfaceAndColors();
}

void Chunk::cacheSurfaceAndColors() {
	if (lazyInited) {
		return cacheSurfaceAndColorsLazy();
	}
	return cacheSurfaceAndColorsIndustrious();
}
void Chunk::cacheSurfaceAndColorsLazy() {
	/*cachedFloatSurface.clear();
	cachedFloatColors.clear();*/
	cachedFloatSurfaceAndColors.clear();

	for (auto it = cachedVoxelSurface->begin(); it != cachedVoxelSurface->end(); it++) {
		Triple<long, long, long> key = (*it).first;
		Voxel vox = (*it).second;
		cachedFloatSurfaceAndColors.push_back((float)key.first);
		cachedFloatSurfaceAndColors.push_back((float)key.second);
		cachedFloatSurfaceAndColors.push_back((float)key.third);

		glm::vec3* color = ChunkType::getColor(vox.type);
		cachedFloatSurfaceAndColors.push_back(color->x);
		cachedFloatSurfaceAndColors.push_back(color->y);
		cachedFloatSurfaceAndColors.push_back(color->z);
		delete color;
	}
}
void Chunk::cacheSurfaceAndColorsIndustrious() {
	cachedFloatSurfaceAndColors.clear();
	cachedFloatSurfaceAndColors.clear();

	for (int i = 0; i < CHUNK_SIZE; i++) {
		for (int j = 0; j < CHUNK_SIZE; j++) {
			for (int k = 0; k < CHUNK_HEIGHT; k++) {
				if (voxels[i][j][k].active
					&& isVoxelOnSurface(i, j, k)) {
					cachedFloatSurfaceAndColors.push_back((float)(chunkX + i));
					cachedFloatSurfaceAndColors.push_back((float)(chunkY + j));
					cachedFloatSurfaceAndColors.push_back((float)k);

					glm::vec3* color = ChunkType::getColor(voxels[i][j][k].type);
					cachedFloatSurfaceAndColors.push_back(color->x);
					cachedFloatSurfaceAndColors.push_back(color->y);
					cachedFloatSurfaceAndColors.push_back(color->z);
					delete color;
				}
			}
		}
	}
}

//std::pair<long, float*> Chunk::getVoxelPositionsToRender() {
//	cacheVoxelData();
//	long size = cachedFloatSurface.size();
//	if (size == 0) {
//		return std::pair<long, float*>(0, nullptr);
//	}
//	return std::pair<long,float*>{size, &(cachedFloatSurface[0])};
//}
//std::pair<long, float*> Chunk::getVoxelColorsToRender() {
//	cacheVoxelData();
//	long size = cachedFloatColors.size();
//	if (size == 0) {
//		return std::pair<long, float*>(0, nullptr);
//	}
//	return std::pair<long, float*>{size, & (cachedFloatColors[0])};
//}
std::pair<long, float*> Chunk::getPositionsAndColorsToRender() {
	cacheVoxelData();
	long size = cachedFloatSurfaceAndColors.size();
	if (size == 0) {
		return std::pair<long, float*>(0, nullptr);
	}
	return std::pair<long, float*>{size, & (cachedFloatSurfaceAndColors[0])};
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

int Chunk::getChunkX() const { return chunkX; }
int Chunk::getChunkY() const { return chunkY; }