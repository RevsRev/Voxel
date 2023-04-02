#pragma once

#include <gui/Camera.h>
#include <gui/draw/ChunkRenderer.h>
#include <gui/GuiUpdatable.h>
#include <set>
#include <map>
#include <struc/World.h>
#include <future>
#include <io/ChunkCache.h>
#include <util/pattern/pubsub/Subscriber.h>
#include "glm/gtc/type_ptr.hpp"
#include <util/data/ObjectPool.h>
#include <util/data/Loader.h>
#include <mutex>

class WorldUi : public GuiUpdatable, private Subscriber<Chunk> {
private:
	std::set<Camera*> cameras{};

	ObjectPool<std::pair<long, long>, Chunk> pool = NULL;

	Camera* selectedCamera = nullptr;
	const World* world;

	//All for making sure we render chunks properly
	std::mutex queueLock{};
	std::mutex renderLock{};
	std::mutex rendererRecycleLock{};
	std::map<std::pair<long, long>, Chunk*> chunkQueue{};
	std::map<std::pair<long, long>, ChunkRenderer*> renderers{};
	std::vector<ChunkRenderer*> renderersToRecycle{};

	unsigned char renderDistance = 20;
	long chunkX;
	long chunkY;

	bool firstChunkCache = true;
	double lastChunkCacheX;
	double lastChunkCacheY;
	double lastChunkCacheZ;

	bool updateChunkPosition();
	void flushChunkPool();

	void flushChunkQueue();
	void flushRenderersToDelete();

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

	//TODO - extract into some sort of render manager
	void onCreate(Chunk& val) override;
	void onUpdate(Chunk& val) override;
	void onDelete(Chunk& val) override;
};