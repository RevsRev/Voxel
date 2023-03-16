#include <phys/GameEngine.h>

//TODO - Not thread safe but good enough for now...
void physLoop::physics_loop(GameEngine* engine) {
	if (started_engine_thread) {
		return;
	}

	engine->physicsLoop();
	started_engine_thread = false;
}


GameEngine* GameEngine::the() {
	static GameEngine* theEngine = new GameEngine;
	return theEngine;
}
GameEngine::GameEngine() {}

void GameEngine::physicsLoop() {
	if (state != STARTING) {
		return;
	}
	state = RUNNING;

	while (state = RUNNING) {
		for (auto it = objects.begin(); it != objects.end(); it++) {
			GameObject* obj = *it;
			obj->updatePosition(1);
		}
		//TODO - sort out frame rate properly
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	engineThread = nullptr;
	state = STOPPED;
}


void GameEngine::start() {
	if (state != STOPPED) {
		return;
	}

	state = STARTING;
	engineThread = new std::thread(physLoop::physics_loop, this);
}
void GameEngine::stop() {
	state = STOPPING;
}

void GameEngine::addObject(GameObject* object) {
	objects.insert(object);
}
void GameEngine::removeObject(GameObject* object) {
	objects.erase(object);
}