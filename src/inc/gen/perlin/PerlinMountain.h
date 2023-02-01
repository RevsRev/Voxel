#pragma once

#include <gen/perlin/PerlinPostProcessor.h>

class PerlinMountain : public PerlinPostProcessor {
public:
	PerlinMountain(long seed, unsigned int resolution, unsigned int height);
	float postProcess(float result);
};