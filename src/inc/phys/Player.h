#pragma once

#include <phys/PhysicalObject.h>
#include <gui/draw/ChunkRenderer.h>
#include <gui/Camera.h>
#include <map>
#include <gui/GuiUpdatable.h>
#include <utility>
#include <set>
#include <cmath>

class Player : public PhysicalObject, public GuiUpdatable{

private:
	Camera playerCam;
	std::map<std::pair<long,long>, ChunkRenderer*> renderers{};
	unsigned char renderDistance = 10;

private:
	void updateChunkRenderers();
	std::set<std::pair<long,long>> getChunksToRender();

public:
	Player(double x, double y, double z);

	void update(float delTime);

};