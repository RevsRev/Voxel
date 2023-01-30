#pragma once

#include <glm/vec3.hpp>
#include <gui/Color.h>

//TODO - Add more at some point!
namespace ChunkType {
	enum CHUNK_TYPES {
		DIRT,
		STONE
	};


	extern glm::vec3* getColor(char chunkType);

}
