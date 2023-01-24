#pragma once

#include "gui/shader/ShaderProgram.h"
#include "Drawable.h"
#include <vector>

class Drawer {
private:
	std::vector<Drawable*> drawables();

public:
	void submit(Drawable* drawable);
	virtual void draw();
};