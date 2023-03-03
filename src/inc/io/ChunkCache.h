#pragma once


#include <struc/Chunk.h>
#include <io/ChunkCacheListener.h>
#include <set>

class ChunkCache {
private:
	std::set<Chunk*> cache{};
	std::map<Chunk*, std::set<void*>> hooks{};

	std::set<ChunkCacheListener*> listeners{};

	void garbageCollect();

public:

	void asyncRequest();
	void asyncRelease();
	void get();

};