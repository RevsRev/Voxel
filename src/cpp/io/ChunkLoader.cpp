#include <io/ChunkLoader.h>

ChunkLoader::ChunkLoader(WorldGenerator* generator) {
	this->generator = generator;
}
ChunkLoader::~ChunkLoader() {
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

Chunk& ChunkLoader::load(std::pair<long, long>& key, std::map<std::string, std::string>& args) {

	//TODO - use the args for lazy chunk loading
	long &chunkX = key.first;
	long &chunkY = key.second;
	return *getChunk(chunkX, chunkY);
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


void ChunkLoader::addToSurface(std::map<Triple<long, long, long>, Voxel>*& cachedVoxelSurface, long& colX, long& colY,
	unsigned char* thisColBitFlags,
	unsigned char* xMinusBitFlags,
	unsigned char* xPlusBitFlags,
	unsigned char* yMinusBitFlags,
	unsigned char* yPlusBitFlags) {

	int charSize = 8*sizeof(unsigned char);
	int bitFlagsSize = Chunk::CHUNK_HEIGHT / charSize;
	for (int i = 0; i < bitFlagsSize; i++) {
		unsigned char thisColBitFlagsLShifted = thisColBitFlags[i] << 1;
		unsigned char thisColBitFlagsRShifted = thisColBitFlags[i] >> 1;
		if (i != bitFlagsSize -1 && ((thisColBitFlags[i + 1] & 128) == 128)) {
			thisColBitFlagsLShifted += 1;
		}
		if (i != 0 && ((thisColBitFlags[i - 1] & 1) == 1)) {
			thisColBitFlagsRShifted += 128;
		}

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

void ChunkLoader::saveToFile(Chunk*& chunk) {
	//TODO - Implement
}

Chunk* ChunkLoader::getChunk(long& chunkX, long& chunkY) {
	if (chunkFileExists(chunkX, chunkY)) {
		return loadFromFile(chunkX, chunkY);
	}
	
	std::chrono::system_clock::time_point genStart = std::chrono::system_clock::now();
	Chunk* chunk = generateChunkLazy(chunkX, chunkY);
	saveToFile(chunk);
	std::chrono::system_clock::time_point genEnd = std::chrono::system_clock::now();
	std::chrono::duration<double> genTime = genEnd - genStart;

	VoxelDiagnostics::the().submitChunkGenTime(genTime.count());

	return chunk;
}

//void ChunkLoader::removeChunk(long& chunkX, long& chunkY) {
//	std::mutex* chunkLock = getChunkLock(chunkX, chunkY);
//	chunkLock->lock();
//
//	Chunk* chunk = chunkCache.at(std::pair<long, long>{chunkX, chunkY});
//	saveToFile(chunk);
//	chunkCache.erase(std::pair<long, long>{chunkX, chunkY});
//	delete chunk;
//
//	chunkLock->unlock();
//}