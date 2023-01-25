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

public:
	PerlinNoise(long seed, unsigned int resolution, unsigned int height);

	float compute(float x, float y);
};