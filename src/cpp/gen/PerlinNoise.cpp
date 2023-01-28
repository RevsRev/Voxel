#include "gen/PerlinNoise.h"

PerlinNoise::PerlinNoise(long seed, unsigned int resolution, unsigned int height) {
	this->seed = seed;
	this->resolution = resolution;
	this->height = height;
}

//TODO - Might need to make this threadsafe at some point?
float PerlinNoise::compute(float x, float y) {
	float scaledX = x / resolution;
	float scaledY = y / resolution;

	//long genSeed = (long)(7507 * sin(x - y) + 1499 * sin(x + y)); //TODO - something better - no symmetry, random, etc...
	//long genSeed = seed;
	long genSeed = seed + floor(x / resolution) + floor(y / resolution);
	srand(genSeed);

	glm::vec2 point{ scaledX, scaledY };

	glm::vec2 bottomLeft{ floor(scaledX), floor(scaledY) };
	glm::vec2 bottomRight{ ceil(scaledX), floor(scaledY) };
	glm::vec2 topLeft{ floor(scaledX), ceil(scaledY) };
	glm::vec2 topRight{ ceil(scaledX), ceil(scaledY) };

	glm::vec2 bottomLeftGrad{ rand(), rand() };
	glm::vec2 bottomRightGrad{ rand(), rand() };
	glm::vec2 topLeftGrad{ rand(), rand() };
	glm::vec2 topRightGrad{ rand(), rand() };

	float n0 = glm::dot(point - bottomLeft, glm::normalize(bottomLeftGrad));
	float n1 = glm::dot(point - bottomRight, glm::normalize(bottomRightGrad));
	float n2 = glm::dot(point - topLeft, glm::normalize(topLeftGrad));
	float n3 = glm::dot(point - topRight, glm::normalize(topRightGrad));

	float sx = scaledX - floor(scaledX);
	float sy = scaledY - floor(scaledY);

	return height*(interpolate(sy, interpolate(sx, n0, n1), interpolate(sx, n2, n3)));
	//return height * (0.1 + interpolate(sx, interpolate(sy, n0, n2), interpolate(sy, n1, n3)));
}

float PerlinNoise::interpolate(float w, float a, float b) {
	return w * (b - a) + a;
}