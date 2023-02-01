# include <gen/perlin/PerlinMountain.h>

PerlinMountain::PerlinMountain(long seed, unsigned int resolution, unsigned int height) : PerlinPostProcessor(seed, resolution, height) {

}

float PerlinMountain::postProcess(float result) {
	//TODO - Decide if this is the right architecture...
	return result;
}