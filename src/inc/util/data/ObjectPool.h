#pragma once

#include <util/data/Cache.h>
#include <util/data/Loader.h>
#include <util/data/MultiValCache.h>
#include <util/pattern/pubsub/Publisher.h>
#include <future>

template <typename K, typename V>
class ObjectPool : private ReadWriteCache<K,V> , public Publisher<V>{
private:

	Loader<K,V>* loader;
	MultiValCache<K, void*> hooks{};

	void gc();

	void request(void* requester, K& key, std::map<std::string, std::string> &args) {
		hooks.put(key, requester);
		if (this->get(key) == nullptr) {
			this->put(key, loader->load(key, args));
			V& value = *this->get(key);
			publishCreate(value);
		}
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

	//TODO - need to implement listeners for updates?

public:

	ObjectPool(Loader<K, V>* loader) {
		this->loader = loader;
	}

	void asyncRequest(void* requester, K& key, std::map<std::string, std::string> &args) {
		std::async(std::launch::async, &ObjectPool<K,V>::request, this, requester, key, args);
	}
	void asyncRelease(void* releaser, K& key) {
		//TODO - Presumably just remove from cache?
		//std::async(std::launch::async, &Loader::load, loader, key);
	}
	V* retrieve(K &key) {
		return get(key);
	}
};