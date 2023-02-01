#include "gen/perlin/PerlinNoise.h"

PerlinNoise::PerlinNoise(long seed, unsigned int resolution, unsigned int height) {
	this->seed = seed;
	this->resolution = resolution;
	this->height = height;
}
PerlinNoise::PerlinNoise() {

}

//TODO - Might need to make this threadsafe at some point?
float PerlinNoise::compute(float x, float y) {
	float scaledX = x / resolution;
	float scaledY = y / resolution;

	glm::vec2 point{ scaledX, scaledY };

	glm::vec2 bottomLeft{ floor(scaledX), floor(scaledY) };
	glm::vec2 bottomRight{ ceil(scaledX), floor(scaledY) };
	glm::vec2 topLeft{ floor(scaledX), ceil(scaledY) };
	glm::vec2 topRight{ ceil(scaledX), ceil(scaledY) };

	glm::vec2 bottomLeftGrad = getRandomVec(floorl(scaledX), floorl(scaledY));
	glm::vec2 bottomRightGrad = getRandomVec(ceill(scaledX), floorl(scaledY));
	glm::vec2 topLeftGrad = getRandomVec(floorl(scaledX), ceill(scaledY));
	glm::vec2 topRightGrad = getRandomVec(ceill(scaledX), ceill(scaledY));

	float n0 = glm::dot(point - bottomLeft, glm::normalize(bottomLeftGrad));
	float n1 = glm::dot(point - bottomRight, glm::normalize(bottomRightGrad));
	float n2 = glm::dot(point - topLeft, glm::normalize(topLeftGrad));
	float n3 = glm::dot(point - topRight, glm::normalize(topRightGrad));

	float sx = scaledX - floor(scaledX);
	float sy = scaledY - floor(scaledY);

	return height*(0.1 + interpolate(sy, interpolate(sx, n0, n1), interpolate(sx, n2, n3)));
	//return height * (0.1 + interpolate(sx, interpolate(sy, n0, n2), interpolate(sy, n1, n3)));
}

float PerlinNoise::interpolate(float w, float a, float b) {
	return w * (b - a) + a;
}

glm::vec2 PerlinNoise::getRandomVec(long cornerX, long cornerY) {
	long genSeed = getGenSeed(cornerX, cornerY);
	srand(genSeed);
	return glm::vec2(rand(), rand());
}

long PerlinNoise::getGenSeed(long cornerX, long cornerY) {
	long genSeed = (long)(7507 * sin(cornerX - cornerY) + 1499 * sin(cornerX + cornerY)); //TODO - something better - no symmetry, random, etc...
	genSeed += seed + 94207 * cornerX + 77, 813 * cornerY;
	return genSeed;
}

void PerlinNoise::setSeed(long seed) {
	this->seed = seed;
}