#pragma once

class ChunkCacheListner {
public:
	virtual void chunkCreated() = 0;
	virtual void chunkUpdated() = 0;
	virtual void chunkDeleted() = 0;
};