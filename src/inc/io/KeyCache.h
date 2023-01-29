#pragma once

#include <GLFW/glfw3.h>

class KeyCache {
private:
	char keyCache[GLFW_KEY_LAST]{};

	void init();

public:
	KeyCache();
	char get(int key);
	void set(int key, char state);
};