#include <gen/WorldGenerator.h>

WorldGenerator::WorldGenerator(long seed) {
	this->seed = seed;
}

float WorldGenerator::generate(long x, long y) {

	float height = 0.0f;

	for (int i = 0; i < postProcessors.size(); i++) {
		height += postProcessors.at(i)->compute(x, y);
	}
	return height;
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