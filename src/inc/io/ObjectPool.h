#pragma once

#include <io/Cache.h>
#include <io/Loader.h>
#include <io/MultiValCache.h>

template <typename K, typename V>
class ObjectPool : private ReadWriteCache<K,V>{
private:

	Loader<K, V>* loader;
	MultiValCache<K, void*> hooks{};

	void gc();

	void request(void* requester, K& key) {
		hooks.put(key, requester);
		this->put(key, loader->load(key));
	}
	void release(void* releaser, K& key) {
		ReadWriteSet<void*> keyHooks = hooks.get(key);
		keyHooks.remove(releaser);
		if (keyHooks.isEmpty()) {
			this->remove(key);
			//TODO - Way to remove from hooks (small memory leak here...)
			//TODO - error handling (need to keep the ReadWriteCache and hooks in sync with one another)
		}
	}

public:

	ObjectPool(Loader<K, V>* loader) {
		this->loader = loader;
	}

	void asyncRequest(void* requester, K& key);
	void asyncRelease(void* releaser, K& key);
	V* retrieve();
};