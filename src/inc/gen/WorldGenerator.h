#pragma once

#include <vector>
#include <gen/perlin/PerlinPostProcessor.h>

class WorldGenerator {
private:
	long seed;
	std::vector<PerlinPostProcessor*> postProcessors{};

public:
	WorldGenerator(long seed);

	void addPostProcessor(PerlinPostProcessor* postProcessor);
	float generate(long x, long y);
};