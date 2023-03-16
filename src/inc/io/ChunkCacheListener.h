#pragma once

class ChunkCacheListener {
public:
	virtual void chunkCreated(Chunk* chunk) = 0;
	virtual void chunkUpdated(Chunk* chunk) = 0;
	virtual void chunkDeleted(Chunk* chunk) = 0;
};