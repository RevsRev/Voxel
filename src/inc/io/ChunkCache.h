#pragma once


#include <struc/Chunk.h>
#include <io/ChunkCacheListener.h>
#include <io/ChunkLoader.h>
#include <set>
#include <future>
#include <thread>


//TODO - this whole class needs to be made thread safe
class ChunkCache {
private:
	ChunkLoader* loader;
	
	std::map<std::pair<long,long>, Chunk*> cache{};
	std::map<std::pair<long, long>, std::future<Chunk*>> futures{};
	std::map<Chunk*, std::set<void*>> hooks{};

	std::set<ChunkCacheListener*> listeners{};

	std::thread cacheThread;
	std::thread gcThread;

	void sendCacheMessages();
	void garbageCollect();

public:

	ChunkCache(ChunkLoader* chunkLoader);

	void asyncRequest(void* &requester, long &chunkX, long &chunkY);
	void asyncRelease(void* &releaser, long &chunkX, long &chunkY);
	Chunk* get(void* &requester, long &chunkX, long &chunkY);

};