#pragma once

#include <concepts>
#include <map>
#include <shared_mutex>
#include <util/data/Cache.h>

template <typename K, typename V>
requires std::equality_comparable<K>
class ReadWriteCache : public Cache<K,V>{
private:
	mutable std::shared_mutex mutex{};
	std::map<K, V> cache;
public:

	void put(const K &key, V &val) override {
		std::unique_lock<std::shared_mutex> lock{ mutex };
		std::pair<const K, V> keyVal{};
		keyVal.first = key;
		//cache.insert({ key, val });
	}
	V* get(const K &key) override {
		std::shared_lock< std::shared_mutex> lock{ mutex };
		if (cache.find(key) != cache.end()) {
			return &cache.at(key);
		}
		return nullptr;
	}
	V* remove(const K &key) override {
		std::unique_lock< std::shared_mutex> lock{ mutex };
		if (cache.find(key) != cache.end()) {
			cache.erase(key);
		}
		return nullptr; //TODO - implement properly
	}

};