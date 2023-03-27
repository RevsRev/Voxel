#pragma once

#include <concepts>
#include <map>
#include <shared_mutex>
#include <util/data/Cache.h>

template <typename K, typename V>
	requires std::equality_comparable<K>&& std::is_copy_constructible<V>::value
class ReadWriteCache : public Cache<K,V>{
private:
	mutable std::shared_mutex mutex{};
	std::map<K, V*> cache;
public:

	void put(const K key, V &val) override {
		//std::unique_lock<std::shared_mutex> lock{ mutex };
		mutex.lock();
		cache.insert({ key, &val });
		mutex.unlock();
	}
	V* get(const K &key) override {
		//std::shared_lock< std::shared_mutex> lock{ mutex };
		mutex.lock_shared();
		if (cache.find(key) != cache.end()) {
			mutex.unlock_shared();
			return cache.at(key);
		}
		mutex.unlock_shared();
		return nullptr;
	}
	V* remove(const K &key) override {
		//std::unique_lock< std::shared_mutex> lock{ mutex };
		mutex.lock_shared();
		auto find = cache.find(key);
		V* retval = nullptr;
		if (find != cache.end()) {
			retval = (* find).second;
			cache.erase(key);
		}
		mutex.unlock_shared();
		return retval; //TODO - implement properly
	}

};