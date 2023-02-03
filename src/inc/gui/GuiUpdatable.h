#pragma once

#include <vector>

class GuiUpdatable {
public:
	virtual void update(float delTime) = 0;
};