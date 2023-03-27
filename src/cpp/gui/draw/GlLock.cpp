#include <gui/draw/GlLock.h>

std::recursive_mutex GlLock::gl_lock{};

void GlLock::lock() {
	gl_lock.lock();
}
void GlLock::unlock() {
	gl_lock.unlock();
}