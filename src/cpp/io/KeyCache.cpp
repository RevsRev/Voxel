#include <io/KeyCache.h>

KeyCache::KeyCache() {
	init();
}

void KeyCache::init() {
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		keyCache[i] = GLFW_RELEASE;
	}
}

char KeyCache::get(int key) {
	return keyCache[key];
}

void KeyCache::set(int key, char state) {
	keyCache[key] = state;
}