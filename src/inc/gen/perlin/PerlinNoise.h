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

	float interpolate(float &w, float &a, float &b);

	glm::vec2 getRandomVec(long &cornerX, long &cornerY);
	long getGenSeed(long &cornerX, long &cornerY);

public:
	PerlinNoise();
	PerlinNoise(long seed, unsigned int resolution, unsigned int height);
	void setSeed(long seed);
	float compute(long &x, long &y);
};