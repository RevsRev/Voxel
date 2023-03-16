#pragma once

#include <phys/GameObject.h>
#include <gui/draw/ChunkRenderer.h>
#include <map>
#include <gui/GuiUpdatable.h>
#include <utility>
#include <set>
#include <cmath>
#include <struc/World.h>
#include <future>
#include <io/KeyBoard.h>
#include <io/Mouse.h>


class Player : public GameObject, public KeyBoardListener, public MouseListener{

private:
	
	

public:
	Player(double x, double y, double z);

	void processKeyEvent(int key, int scancode, int action, int mods);
	void processMouseEvent(double xPos, double yPos);

};