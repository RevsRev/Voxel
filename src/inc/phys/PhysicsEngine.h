#pragma once

#include <set>
#include <iterator>
#include <phys/PhysicalObject.h>
#include <thread>
#include <chrono>

class PhysicsEngine {
private:

	static enum State {
		STARTING,
		RUNNING,
		STOPPING,
		STOPPED
	};
	State state = STOPPED;
	std::thread* engineThread;

	std::set<PhysicalObject*> objects{};
	PhysicsEngine();

public:
	static PhysicsEngine* the();
	void start();
	void stop();

	void physicsLoop();

	void addObject(PhysicalObject* object);
	void removeObject(PhysicalObject* object);

	friend PhysicalObject;
};

namespace physLoop {
	static bool started_engine_thread;
	extern void physics_loop(PhysicsEngine* engine);
}