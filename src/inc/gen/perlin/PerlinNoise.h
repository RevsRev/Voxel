#pragma once

#include <stdlib.h>
#include <cmath>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class PerlinNoise {
private:
	long seed;
	unsigned int resolution;
	unsigned int height;

	float interpolate(float w, float a, float b);

	long getGenSeed(float x, float y);

public:
	PerlinNoise();
	PerlinNoise(long seed, unsigned int resolution, unsigned int height);
	void setSeed(long seed);
	float compute(float x, float y);
};