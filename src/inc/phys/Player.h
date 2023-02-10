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

class Player : public PhysicalObject, public GuiUpdatable, public KeyBoardListener, public MouseListener{

private:
	
	std::map<std::pair<long,long>, ChunkRenderer*> renderers{};
	unsigned char renderDistance = 10;

private:
	void updateChunkRenderers();
	std::set<std::pair<long,long>> getChunksToRender();

public:
	Player(double x, double y, double z);

	//TODO - Make private, improve composite physical objects?
	Camera playerCam;

	void update(float delTime);
	void render(); //TODO - Extract to an interface?

	void processKeyEvent(int key, int scancode, int action, int mods);
	void processMouseEvent(double xPos, double yPos);

};