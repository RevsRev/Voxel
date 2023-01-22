#pragma once

#include "Chunk.h"
#include <glm/vec3.hpp>

namespace Coord {
	const static unsigned int VOXEL_PHYSICAL_SIZE = 1;
	const static unsigned int CHUNK_PHYSICAL_SIZE = VOXEL_PHYSICAL_SIZE * Chunk::CHUNK_SIZE;
	const static unsigned int CHUNK_PHYSICAL_HEIGHT = VOXEL_PHYSICAL_SIZE * Chunk::CHUNK_HEIGHT;

	extern glm::ivec3* getChunkCoord(glm::dvec3& worldCoord);
	extern glm::ivec3* getVoxelCoord(glm::dvec3& worldCoord);

};