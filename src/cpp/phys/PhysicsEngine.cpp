#include <phys/PhysicsEngine.h>

//TODO - Not thread safe but good enough for now...
void physLoop::physics_loop(PhysicsEngine* engine) {
	if (started_engine_thread) {
		return;
	}

	engine->physicsLoop();
	started_engine_thread = false;
}


PhysicsEngine* PhysicsEngine::the() {
	static PhysicsEngine* theEngine = new PhysicsEngine;
	return theEngine;
}
PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::physicsLoop() {
	if (state != STARTING) {
		return;
	}
	state = RUNNING;

	while (state = RUNNING) {
		for (auto it = objects.begin(); it != objects.end(); it++) {
			PhysicalObject* obj = *it;
			obj->updatePosition(10);
		}
		//TODO - sort out frame rate properly
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	engineThread = nullptr;
	state = STOPPED;
}


void PhysicsEngine::start() {
	if (state != STOPPED) {
		return;
	}

	state = STARTING;
	engineThread = new std::thread(physLoop::physics_loop, this);
}
void PhysicsEngine::stop() {
	state = STOPPING;
}

void PhysicsEngine::addObject(PhysicalObject* object) {
	objects.insert(object);
}
void PhysicsEngine::removeObject(PhysicalObject* object) {
	objects.erase(object);
}