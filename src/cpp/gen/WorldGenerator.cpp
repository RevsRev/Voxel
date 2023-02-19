#include <gen/WorldGenerator.h>

WorldGenerator::WorldGenerator(long seed) {
	this->seed = seed;
}

Voxel* WorldGenerator::generate(long &x, long &y) {

	Voxel* retval = new Voxel[Chunk::CHUNK_HEIGHT];

	float height = 0.0f;

	for (int i = 0; i < postProcessors.size(); i++) {
		height += postProcessors.at(i)->compute(x, y);
	}
	
	for (int i = 0; i < Chunk::CHUNK_HEIGHT; i++) {
		Voxel vox{};
		vox.type = ChunkType::DIRT;
		vox.active = i < height;
		retval[i] = vox;
	}
	return retval;
}

unsigned char* WorldGenerator::generateChunkColumnBitFlags(long &x, long &y) {
	float height = 0.0f;
	for (int i = 0; i < postProcessors.size(); i++) {
		height += postProcessors.at(i)->compute(x, y);
	}
	int iHeight = std::floorl(height);

	int charSize = 8*sizeof(unsigned char);
	int bitFlagsSize = Chunk::CHUNK_HEIGHT / charSize;
	unsigned char* bitFlags = new unsigned char[bitFlagsSize];
	for (int i = 0; i < bitFlagsSize; i++) {
		int startOfChar = charSize * i; //0,8,16,...
		int endOfChar = charSize * (i + 1) - 1; //7,15,23,...
		if (endOfChar <= iHeight) {
			bitFlags[i] = 255;
		}
		else if (startOfChar > iHeight) {
			bitFlags[i] = 0;
		}
		else {
			int diff = iHeight - startOfChar;
			unsigned char bitFlag = 255 << (7 - diff);
			bitFlags[i] = bitFlag;
		}
	}
	return bitFlags;
	/*std::vector<std::pair<long, long>>* retval = new std::vector<std::pair<long, long>>();
	if (iHeight <= Chunk::CHUNK_HEIGHT) {
		retval->push_back(std::pair<long, long>{iHeight, Chunk::CHUNK_HEIGHT});
	}
	return retval;*/
}



void WorldGenerator::addPostProcessor(PerlinPostProcessor* postProcessor) {
	/*PerlinPostProcessor* newProcessor;
	*newProcessor = *postProcessor;
	newProcessor->setSeed(seed);
	postProcessors.push_back(newProcessor);*/
	//TODO - Figure out how to copy??? Maybe...
	postProcessor->setSeed(seed);
	postProcessors.push_back(postProcessor);
}