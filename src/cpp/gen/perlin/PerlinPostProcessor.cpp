#include <gen/perlin/PerlinPostProcessor.h>

PerlinPostProcessor::PerlinPostProcessor(long seed, unsigned int resolution, unsigned int height) {
	noise = PerlinNoise( seed, resolution, height );
}

float PerlinPostProcessor::compute(long x, long y) {
	return postProcess(noise.compute(x, y));
}

void PerlinPostProcessor::setSeed(long seed) {
	noise.setSeed(seed);
}