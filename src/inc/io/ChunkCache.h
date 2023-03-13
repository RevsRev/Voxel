#pragma once


#include <struc/Chunk.h>
#include <io/ChunkCacheListener.h>
#include <io/ChunkLoader.h>
#include <set>
#include <future>
#include <thread>
#include <util/data/ObjectPool.h>

class ChunkCache : public ObjectPool<std::pair<long,long>, Chunk>{
private:

public:
	ChunkCache(WorldGenerator &generator);
};