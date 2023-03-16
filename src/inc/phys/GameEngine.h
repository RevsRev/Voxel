#pragma once

#include <set>
#include <iterator>
#include <phys/GameObject.h>
#include <thread>
#include <chrono>

class GameEngine {
private:

	static enum State {
		STARTING,
		RUNNING,
		STOPPING,
		STOPPED
	};
	State state = STOPPED;
	std::thread* engineThread;

	std::set<GameObject*> objects{};
	GameEngine();

public:
	static GameEngine* the();
	void start();
	void stop();

	void physicsLoop();

	void addObject(GameObject* object);
	void removeObject(GameObject* object);

	friend GameObject;
};

namespace physLoop {
	static bool started_engine_thread;
	extern void physics_loop(GameEngine* engine);
}