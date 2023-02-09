#pragma once

#include <phys/ChunkTypes.h>

//Keep as lightweight as possible, as there will be many of these.
struct Voxel {
public:
	char type = ChunkType::DIRT;
	bool active = false;
};