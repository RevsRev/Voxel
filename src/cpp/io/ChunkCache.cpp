#include <io/ChunkCache.h>

ChunkCache::ChunkCache(ChunkLoader* loader) {
	this->loader = loader;
}

void ChunkCache::asyncRequest(void* &requester, long &chunkX, long &chunkY) {
	std::future<Chunk*>* chunkFuture = &std::async(std::launch::async, &ChunkLoader::getChunk, loader, std::ref(chunkX), std::ref(chunkY));
}
void ChunkCache::asyncRelease(void* &releaser, long& chunkX, long& chunkY) {
	std::pair<long, long> key{ chunkX, chunkY };
	auto chunkFinder = cache.find(key);
	if (chunkFinder == cache.end()) {
		return;
	}
	Chunk* chunk = chunkFinder->second;

	auto hookFinder = hooks.find(chunk);
	if (hookFinder == hooks.end()) {
		return;
	}

	std::set<void*> *hook = &hookFinder->second;
	if (hook->find(releaser) != hook->end()) {
		hook->erase(releaser);
	}
}

void ChunkCache::sendCacheMessages() {
	//TODO - implement

}
void ChunkCache::garbageCollect() {
	for (auto it = hooks.begin(); it != hooks.end(); it++) {
		if ((*it).second.empty()) {
			Chunk* chunkToDelete = (*it).first;
			long chunkX = chunkToDelete->getChunkX();
			long chunkY = chunkToDelete->getChunkY();
			std::pair<long, long> key{ chunkX, chunkY };
			cache.erase(key);
			if (futures.find(key) != futures.end()) {
				futures.erase(key);
			}
			//TODO - fire the deleted message to the listeners
			//TODO - need to delete the thing it points at too...
			std::async(std::launch::async, &ChunkLoader::removeChunk, loader, std::ref(chunkX), std::ref(chunkY));
		}
	}
}

Chunk* ChunkCache::get(void* &requester, long& chunkX, long& chunkY) {
	std::pair<long, long> key{ chunkX,chunkY };
	if (cache.find(key) != cache.end()) {
		Chunk* retval = cache.at(key);

		auto hooksFinder = hooks.find(retval);
		if (hooksFinder == hooks.end()) {
			return nullptr;
		}

		std::set<void*>* thisChunkHooks = &(*hooksFinder).second;
		if (thisChunkHooks->find(requester) == thisChunkHooks->end()) {
			thisChunkHooks->insert(requester);
		}
		return retval;
	}
	return nullptr;
}