#pragma once

#include <mutex>

namespace GlLock {
	extern std::recursive_mutex gl_lock;

	extern void lock();
	extern void unlock();
}