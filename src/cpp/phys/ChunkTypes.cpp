#include <phys/ChunkTypes.h>

glm::vec3* ChunkType::getColor(char chunkType) {
	switch (chunkType) {
	case ChunkType::CHUNK_TYPES::DIRT:
		return Color::getAsGlmVec3(&Color::BROWN[0]);
	case ChunkType::CHUNK_TYPES::STONE:
		return Color::getAsGlmVec3(&Color::GREY[0]);
	}
}