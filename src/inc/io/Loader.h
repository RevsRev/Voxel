#pragma once

#include <struc/Chunk.h>


template <typename K, typename V>
class Loader {
	virtual V* load(K &key) = 0;
};

//TODO - Implement, move elsewhere
class ChunkLoaderTest : public Loader<std::pair<long, long>, Chunk> {
public:
	Chunk* load(std::pair<long,long> &key) override {
		return nullptr;
	}
};