#include "struc/Coord.h"

glm::ivec3* Coord::getChunkCoord(glm::dvec3& worldCoord) {
	return new glm::ivec3(worldCoord.x / Coord::CHUNK_PHYSICAL_SIZE, worldCoord.y / Coord::CHUNK_PHYSICAL_SIZE, 0);
}

glm::ivec3* Coord::getVoxelCoord(glm::dvec3& worldCoord) {
	return new glm::ivec3(worldCoord.x / Coord::CHUNK_PHYSICAL_SIZE, worldCoord.y / Coord::CHUNK_PHYSICAL_SIZE, worldCoord.z / Coord::CHUNK_PHYSICAL_HEIGHT);
}