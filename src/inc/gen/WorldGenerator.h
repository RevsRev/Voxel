#pragma once

#include <vector>
#include <gen/perlin/PerlinPostProcessor.h>
#include <struc/Voxel.h>
#include <struc/Chunk.h>
#include <cmath>

class WorldGenerator {
private:
	long seed;
	std::vector<PerlinPostProcessor*> postProcessors{};

public:
	WorldGenerator(long seed);

	void addPostProcessor(PerlinPostProcessor* postProcessor);
	Voxel* generate(long &x, long &y);
	std::vector<std::pair<long, long>>* generateSurfaceSeeds(long &x, long &y);
};