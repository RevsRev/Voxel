#include "struc/World.h"

World* World::the() {
	static World* theWindow = new World();
	return theWindow;
}

World::World() {

	initGenerator();

	//TODO - extract elsewhere. Get rid of magic numbers
	int chunkXRange = 20;
	int chunkYRange = 20;
}

void World::initGenerator() {
	unsigned int resolution = 30;
	unsigned int height = 50;
	PerlinMountain* mountain = new PerlinMountain(seed, resolution, height);
	PerlinMountain* moreMountain = new PerlinMountain(seed, 78, 100);
	generator.addPostProcessor(mountain);
	generator.addPostProcessor(moreMountain);
}

ChunkLoader* World::getChunkLoader() {
	return &loader;
}

WorldGenerator* World::getWorldGenerator() {
	return &generator;
}