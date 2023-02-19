#include <io/ChunkLoader.h>

ChunkLoader::ChunkLoader(WorldGenerator* generator) {
	this->generator = generator;
	initChunkLocks();
}
ChunkLoader::~ChunkLoader() {
	/*destroyChunkLocks();
	destroyChunks();*/

	//TODO - Not too bothered at the moment because this is only destroyed on application exit at the moment.
}

bool ChunkLoader::chunkFileExists(long &chunkX, long &chunkY) {
	//TODO - Implement
	return false;
}

Chunk* ChunkLoader::loadFromFile(long &chunkX, long& chunkY) {
	//TODO - Implement
	return nullptr;
}

Chunk* ChunkLoader::generateChunk(long& chunkX, long& chunkY) {
	Voxel*** voxels = new Voxel * *[Chunk::CHUNK_SIZE];
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++) {
		voxels[i] = new Voxel * [Chunk::CHUNK_SIZE];
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++) {
			long x = chunkX * Chunk::CHUNK_SIZE + i;
			long y = chunkY * Chunk::CHUNK_SIZE + j;
			voxels[i][j] = generator->generate(x,y);
		}
	}
	return new Chunk(voxels, Chunk::CHUNK_SIZE*chunkX, Chunk::CHUNK_SIZE*chunkY);
}

Chunk* ChunkLoader::generateChunkLazy(long &chunkX, long &chunkY) {

	long chunkXCoord = chunkX * Chunk::CHUNK_SIZE;
	long chunkYCoord = chunkY * Chunk::CHUNK_SIZE;

	std::map<std::pair<long, long>, unsigned char*> columnBitFlags{};
	for (int i = 0; i <= Chunk::CHUNK_SIZE + 1; i++) { //include the sides of the adjacent chunks
		for (int j = 0; j <= Chunk::CHUNK_SIZE + 1; j++) {
			std::pair<long, long> key{ chunkXCoord + i - 1, chunkYCoord + j - 1};
			columnBitFlags.insert({ key, generator->generateChunkColumnBitFlags(key.first, key.second) });
		}
	}

	std::map<Triple<long, long, long>, Voxel>* cachedVoxelSurface = new std::map<Triple<long, long, long>, Voxel>();
	for (int i = 0; i < Chunk::CHUNK_SIZE; i++) {
		for (int j = 0; j < Chunk::CHUNK_SIZE; j++) {
			unsigned char* mySeeds = columnBitFlags.at(std::pair<long, long>{ chunkXCoord + i, chunkYCoord + j });
			unsigned char* xMinusBitFlags = columnBitFlags.at(std::pair<long, long>{ chunkXCoord + i - 1, chunkYCoord + j });
			unsigned char* xPlusBitFlags = columnBitFlags.at(std::pair<long, long>{ chunkXCoord + i + 1, chunkYCoord + j });
			unsigned char* yMinusBitFlags = columnBitFlags.at(std::pair<long, long>{ chunkXCoord + i, chunkYCoord + j - 1 });
			unsigned char* yPlusBitFlags = columnBitFlags.at(std::pair<long, long>{ chunkXCoord + i, chunkYCoord + j + 1 });

			long x = chunkXCoord + i;
			long y = chunkYCoord + j;

			addToSurface(cachedVoxelSurface, x, y, mySeeds, xMinusBitFlags, xPlusBitFlags, yMinusBitFlags, yPlusBitFlags);
		}
	}

	int charSize = 8 * sizeof(unsigned char);
	int bitFlagsSize = Chunk::CHUNK_HEIGHT / charSize;
	auto it = columnBitFlags.begin();
	while (it != columnBitFlags.end()) {
		unsigned char* bitFlag = (*it).second;
		it++;
		delete[] bitFlag;
	}

	return new Chunk(cachedVoxelSurface, chunkX, chunkY);
}


//TODO - This isn't quite right. Should also optimise
void ChunkLoader::addToSurface(std::map<Triple<long, long, long>, Voxel>*& cachedVoxelSurface, long& colX, long& colY,
	unsigned char* thisColBitFlags,
	unsigned char* xMinusBitFlags,
	unsigned char* xPlusBitFlags,
	unsigned char* yMinusBitFlags,
	unsigned char* yPlusBitFlags) {

	int charSize = 8*sizeof(unsigned char);
	int bitFlagsSize = Chunk::CHUNK_HEIGHT / charSize;
	//unsigned char* surfaceBitFlags = new unsigned char[bitFlagsSize];
	for (int i = 0; i < bitFlagsSize; i++) {
		unsigned char thisColBitFlagsLShifted = thisColBitFlags[i] << 1;
		unsigned char thisColBitFlagsRShifted = thisColBitFlags[i] >> 1;
		if (i != bitFlagsSize -1 && ((thisColBitFlags[i + 1] & 128) == 128)) {
			thisColBitFlagsLShifted += 1;
		}
		if (i != 0 && ((thisColBitFlags[i - 1] & 1) == 1)) {
			thisColBitFlagsRShifted += 128;
		}

		//std::cout << "lShift, char, rShift = " << (int)thisColBitFlagsLShifted << " , " << (int)thisColBitFlags[i] << " , " << (int)thisColBitFlagsRShifted << std::endl;

		//The left shifted and right shifted bit flags can be XORd with the bit flags to detect changes. This then gives us all the edges from within this bitflag.
		unsigned char surfaceBitFlags = ((thisColBitFlagsLShifted ^ thisColBitFlags[i]) | (thisColBitFlagsRShifted ^ thisColBitFlags[i]) & thisColBitFlags[i]);

		//Now saturate with the edges inherited from our neighbours.
		surfaceBitFlags = surfaceBitFlags | (thisColBitFlags[i] & (~xMinusBitFlags[i] | ~xPlusBitFlags[i] | ~yMinusBitFlags[i] | ~yPlusBitFlags[i]));

		for (int j = 0; j < charSize; j++) {
			unsigned char twoToTheJ = 1 << j;
			if ((surfaceBitFlags & twoToTheJ) == twoToTheJ) {
				Triple<long, long, long> key{ colX, colY, (i+1)*charSize - j}; //bottom of each char corresponds to the lower z coordinate
				Voxel vox{};
				vox.active = true;
				vox.type = ChunkType::DIRT; //TODO - This needs to be extracted elsewhere.
				cachedVoxelSurface->insert({ key, vox });
			}
		}
	}
}


	//std::vector<long> zCoordsToAdd{};
	//for (int i = 0; i < neighbour->size(); i++) {
	//	long neighbourFirstAir = neighbour->at(i).first;
	//	long neighbourSecondAir = neighbour->at(i).first;
	//	
	//	for (int j = neighbourFirstAir; j <= neighbourSecondAir; j++) {
	//		zCoordsToAdd.push_back(j);
	//	}
	//}

	//if (colBeingConsidered != neighbour) //because I'm lazy and don't want to write another method right now.
	//{
	//	for (int i = 0; i < colBeingConsidered->size(); i++) {
	//		long firstAir = colBeingConsidered->at(i).first;
	//		long secondAir = colBeingConsidered->at(i).second;

	//		for (int j = firstAir; j <= secondAir; j++) {
	//			for (int k = zCoordsToAdd.size() - 1; k >= 0; k--) {
	//				if (zCoordsToAdd.at(k) == j) {
	//					zCoordsToAdd.erase(zCoordsToAdd.begin() + k);
	//				}
	//			}
	//		}
	//	}
	//}

	//for (int i = 0; i < zCoordsToAdd.size(); i++) {
	//	Triple<long, long, long> key{ colX, colY, zCoordsToAdd.at(i)};
	//	Voxel vox{};
	//	vox.active = true;
	//	vox.type = ChunkType::DIRT; //TODO - This needs to be extracted elsewhere.
	//	cachedVoxelSurface->insert({ key,vox });
	//}
//}

	//std::set<long> zCoordsToAdd{};

	//for (int i = 0; i < neighbour->size(); i++) {
	//	long neighbourFirstAir = neighbour->at(i).first;
	//	long neighbourSecondAir = neighbour->at(i).first;
	//	
	//	for (int j = neighbourFirstAir; j <= neighbourSecondAir; j++) {
	//		zCoordsToAdd.insert(j);
	//	}
	//}

	//if (colBeingConsidered != neighbour) //because I'm lazy and don't want to write another method right now.
	//{
	//	for (int i = 0; i < colBeingConsidered->size(); i++) {
	//		long firstAir = colBeingConsidered->at(i).first;
	//		long secondAir = colBeingConsidered->at(i).second;

	//		for (int j = firstAir; j <= secondAir; j++) {
	//			auto find = zCoordsToAdd.find(j);
	//			if (find != zCoordsToAdd.end()) {
	//				zCoordsToAdd.erase(j);
	//			}
	//		}
	//	}
	//}
	//
	//for (auto it = zCoordsToAdd.begin(); it != zCoordsToAdd.end(); it++) {
	//	Triple<long,long,long> key{ colX, colY, (*it) };
	//	Voxel vox{};
	//	vox.active = true;
	//	vox.type = ChunkType::DIRT; //TODO - This needs to be extracted elsewhere.
	//	cachedVoxelSurface->insert({ key,vox });
	//}
//}

void ChunkLoader::saveToFile(Chunk*& chunk) {
	//TODO - Implement
}

Chunk* ChunkLoader::getChunk(long& chunkX, long& chunkY) {
	std::mutex* chunkLock = getChunkLock(chunkX, chunkY);
	chunkLock->lock();

	Chunk* chunk;
	chunk = getFromCache(std::pair<long, long>{chunkX, chunkY});
	if (chunk != nullptr) {
		chunkLock->unlock();
		return chunk;
	}

	if (chunkFileExists(chunkX, chunkY)) {
		chunk = loadFromFile(chunkX, chunkY);
	}
	else {
		//chunk = generateChunk(chunkX, chunkY);
		chunk = generateChunkLazy(chunkX, chunkY);
		saveToFile(chunk);
	}
	chunkCache.insert({ std::pair<long, long>{chunkX, chunkY}, chunk });
	//recacheNeighbours(chunkX, chunkY);

	chunkLock->unlock();

	return chunk;
}

void ChunkLoader::removeChunk(long& chunkX, long& chunkY) {
	std::mutex* chunkLock = getChunkLock(chunkX, chunkY);
	chunkLock->lock();

	Chunk* chunk = chunkCache.at(std::pair<long, long>{chunkX, chunkY});
	saveToFile(chunk);
	chunkCache.erase(std::pair<long, long>{chunkX, chunkY});
	delete chunk;

	chunkLock->unlock();
}

//TODO - This is a bit ugly... tidy up at some point.
//void ChunkLoader::recacheNeighbours(long& chunkX, long& chunkY) {
//	Chunk* thisChunk = getFromCache(std::pair<long, long>{chunkX, chunkY});
//
//	Chunk* leftNeighbour = getFromCache(std::pair<long, long>{chunkX - 1, chunkY});
//	Chunk* rightNeighbour = getFromCache(std::pair<long, long>{chunkX + 1, chunkY});
//	Chunk* bottomNeighbour = getFromCache(std::pair<long, long>{chunkX, chunkY - 1});
//	Chunk* topNeighbour = getFromCache(std::pair<long, long>{chunkX, chunkY + 1});
//
//	cacheNeighbour(Chunk::X_MINUS, thisChunk, leftNeighbour);
//	if (leftNeighbour != nullptr) {
//		cacheNeighbour(Chunk::X_PLUS, leftNeighbour, thisChunk);
//	}
//
//	cacheNeighbour(Chunk::X_PLUS, thisChunk, rightNeighbour);
//	if (rightNeighbour != nullptr) {
//		cacheNeighbour(Chunk::X_MINUS, rightNeighbour, thisChunk);
//	}
//
//	cacheNeighbour(Chunk::Y_MINUS, thisChunk, bottomNeighbour);
//	if (bottomNeighbour != nullptr) {
//		cacheNeighbour(Chunk::Y_PLUS, bottomNeighbour, thisChunk);
//	}
//
//	cacheNeighbour(Chunk::Y_PLUS, thisChunk, topNeighbour);
//	if (topNeighbour != nullptr) {
//		cacheNeighbour(Chunk::Y_MINUS, topNeighbour, thisChunk);
//	}
//}
//
//void ChunkLoader::cacheNeighbour(int& neighbour, Chunk*& thisChunk, Chunk*& thatChunk) {
//	thisChunk->setNeighbour(neighbour, thatChunk);
//}

Chunk* ChunkLoader::getFromCache(std::pair<long, long>& key) {
	if (chunkCache.find(key) == chunkCache.end()) {
		return nullptr;
	}
	return chunkCache.at(key);
}

void ChunkLoader::initChunkLocks() {
	for (int i = 0; i < chunkLocksSize; i++) {
		for (int j = 0; j < chunkLocksSize; j++) {
			std::pair<long, long> key{ i,j };
			std::mutex* chunkLock = new std::mutex();
			chunkLocks.insert(std::pair < std::pair<long, long>, std::mutex*> { key, chunkLock });
		}
	}
}

//TODO - Make this more elegant (what happens if a lock is acquired while we delete? Although this scenario is unrealistic...)
void ChunkLoader::destroyChunkLocks() {
	for (int i = 0; i < chunkLocksSize; i++) {
		for (int j = 0; j < chunkLocksSize; j++) {
			std::pair<long, long> key{ i,j };
			std::mutex* chunkLock = chunkLocks.at(key);
			chunkLocks.erase(key);
			delete chunkLock;
		}
	}
}

std::mutex* ChunkLoader::getChunkLock(long& chunkX, long& chunkY) {
	long keyX = (chunkX % chunkLocksSize + chunkLocksSize) % chunkLocksSize;
	long keyY = (chunkY % chunkLocksSize + chunkLocksSize) % chunkLocksSize;

	std::pair<long, long> key{keyX, keyY };
	return chunkLocks.at(key);
}
