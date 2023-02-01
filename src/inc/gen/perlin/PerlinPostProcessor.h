#pragma once

#include <gen/perlin/PerlinNoise.h>

class PerlinPostProcessor {
private:
	PerlinNoise noise;

public:
	PerlinPostProcessor(long seed, unsigned int resolution, unsigned int height);
	void setSeed(long seed);
	
	float compute(long x, long y);

	virtual float postProcess(float result) = 0;
};