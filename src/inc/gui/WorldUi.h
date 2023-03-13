#pragma once

#include <gui/Camera.h>
#include <gui/draw/ChunkRenderer.h>
#include <gui/GuiUpdatable.h>
#include <set>
#include <struc/World.h>
#include <future>
#include <io/ChunkCacheListener.h>
#include "glm/gtc/type_ptr.hpp"
#include <io/ObjectPool.h>
#include <io/Loader.h>

class WorldUi : public GuiUpdatable, public ChunkCacheListener {
private:
	std::set<Camera*> cameras{};

	ObjectPool<std::pair<long,long>,Chunk> pool{new ChunkLoaderTest()};

	Camera* selectedCamera = nullptr;
	const World* world;

	//All for making sure we render chunks properly
	std::map<std::pair<long, long>, ChunkRenderer*> renderers{};
	unsigned char renderDistance = 10;
	long chunkX;
	long chunkY;

	bool firstChunkCache = true;
	double lastChunkCacheX;
	double lastChunkCacheY;
	double lastChunkCacheZ;

	bool updateChunkPosition();
	void updateChunkRenderers();
	std::set<std::pair<long, long>> getChunksToRender();
	std::set<std::pair<long, long>> getChunksToDelete();

	std::future<void>* deleteChunkAsync(long& chunkX, long& chunkY);
	std::future<Chunk*>* getChunkAsync(long& chunkX, long& chunkY);
	Chunk* getChunk(long& chunkX, long& chunkY);

	bool checkRenderDistance(long& chunkX, long& chunkY);

public:

	WorldUi(World* world);

	void update(float delTime);

	void addCamera(Camera* camera);
	void setSelectedCamera(Camera* camera);

	void render(); //TODO - Extract to an interface?

	void chunkCreated(Chunk* chunk);
	void chunkUpdated(Chunk* chunk);
	void chunkDeleted(Chunk* chunk);

};