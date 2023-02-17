#pragma once

#include <phys/PhysicalObject.h>
#include <gui/draw/ChunkRenderer.h>
#include <gui/Camera.h>
#include <map>
#include <gui/GuiUpdatable.h>
#include <utility>
#include <set>
#include <cmath>
#include <struc/World.h>
#include "glm/gtc/type_ptr.hpp"
#include <future>


class Player : public PhysicalObject, public GuiUpdatable, public KeyBoardListener, public MouseListener{

private:
	
	std::map<std::pair<long,long>, ChunkRenderer*> renderers{};
	unsigned char renderDistance = 30;
	long chunkX;
	long chunkY;

	bool firstChunkCache = true;
	double lastChunkCacheX;
	double lastChunkCacheY;
	double lastChunkCacheZ;

	bool updateChunkPosition();
	void updateChunkRenderers();
	std::set<std::pair<long,long>> getChunksToRender();
	std::set<std::pair<long,long>> getChunksToDelete();

	std::future<void>* deleteChunkAsync(long chunkX, long chunkY);
	std::future<Chunk*>* getChunkAsync(long chunkX, long chunkY);
	Chunk* getChunk(long chunkX, long chunkY);

public:
	Player(double x, double y, double z);

	//TODO - Make private, improve composite physical objects?
	Camera playerCam;

	void update(float delTime);
	void render(); //TODO - Extract to an interface?

	void processKeyEvent(int key, int scancode, int action, int mods);
	void processMouseEvent(double xPos, double yPos);

};