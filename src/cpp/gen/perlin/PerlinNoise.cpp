#include "gen/perlin/PerlinNoise.h"

PerlinNoise::PerlinNoise(long seed, unsigned int resolution, unsigned int height) {
	this->seed = seed;
	this->resolution = resolution;
	this->height = height;
}
PerlinNoise::PerlinNoise() {

}

float PerlinNoise::compute(long &x, long &y) {
	float scaledX = (float)x / resolution;
	float scaledY = (float)y / resolution;

	long scaledXBottomL = floorl(scaledX);
	long scaledYBottomL = floorl(scaledY);
	long scaledXTopL = ceill(scaledX);
	long scaledYTopL = ceill(scaledY);

	glm::vec2 point{ scaledX, scaledY };

	glm::vec2 bottomLeft{ floor(scaledX), floor(scaledY) };
	glm::vec2 bottomRight{ ceil(scaledX), floor(scaledY) };
	glm::vec2 topLeft{ floor(scaledX), ceil(scaledY) };
	glm::vec2 topRight{ ceil(scaledX), ceil(scaledY) };

	glm::vec2 bottomLeftGrad = getRandomVec(scaledXBottomL, scaledYBottomL);
	glm::vec2 bottomRightGrad = getRandomVec(scaledXTopL, scaledYBottomL);
	glm::vec2 topLeftGrad = getRandomVec(scaledXBottomL, scaledYTopL);
	glm::vec2 topRightGrad = getRandomVec(scaledXTopL, scaledYTopL);

	float n0 = glm::dot(point - bottomLeft, glm::normalize(bottomLeftGrad));
	float n1 = glm::dot(point - bottomRight, glm::normalize(bottomRightGrad));
	float n2 = glm::dot(point - topLeft, glm::normalize(topLeftGrad));
	float n3 = glm::dot(point - topRight, glm::normalize(topRightGrad));

	float sx = scaledX - floor(scaledX);
	float sy = scaledY - floor(scaledY);

	float firstInterpolate = interpolate(sx, n0, n1);
	float secondInterpolate = interpolate(sx, n2, n3);
	return height*(0.1 + interpolate(sy, firstInterpolate, secondInterpolate));
}

float PerlinNoise::interpolate(float &w, float &a, float &b) {
	return w * (b - a) + a;
}

glm::vec2 PerlinNoise::getRandomVec(long &cornerX, long &cornerY) {
	long genSeed = getGenSeed(cornerX, cornerY);
	std::minstd_rand stdRand{};
	stdRand.seed(genSeed);
	return glm::vec2(stdRand(), stdRand());
}

long PerlinNoise::getGenSeed(long &cornerX, long &cornerY) {
	long genSeed = (long)(7507 * sin(cornerX - cornerY) + 1499 * sin(cornerX + cornerY)); //TODO - something better - no symmetry, random, etc...
	genSeed += seed + 94207 * cornerX + 77, 813 * cornerY;
	return genSeed;
}

void PerlinNoise::setSeed(long seed) {
	this->seed = seed;
}