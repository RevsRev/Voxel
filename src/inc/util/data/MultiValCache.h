#pragma once

#include <util/data/Cache.h>
#include <util/data/ReadWriteCache.h>
#include <map>
#include <util/data/ReadWriteSet.h>
#include <shared_mutex>

template <typename K, typename V>
	requires std::equality_comparable<K>&& std::is_copy_constructible<V>::value
class MultiValCache {
private:
	mutable std::shared_mutex mutex{};
	ReadWriteCache<K, ReadWriteSet<V>> cache{};

	ReadWriteSet<V>* getSet(K& key) {
		std::shared_lock<std::shared_mutex> readLock{ mutex };
		ReadWriteSet<V>* theSet = cache.get(key);
		if (theSet != nullptr) {
			return theSet;
		}

		readLock.release();
		return initSet(key);
	}
	ReadWriteSet<V>* initSet(K& key) {
		std::unique_lock<std::shared_mutex> uniqueLock{ mutex };
		ReadWriteSet<V>* theSet = cache.get(key);

		//check that there wasn't two threads competing for the unique lock
		if (theSet != nullptr) {
			return theSet;
		}
		theSet = ReadWriteSet<V>{};
		cache.put(key, theSet);
		return &cache.get(key);
	}

public:
	void put(K& key, V& val) {
		ReadWriteSet<V>* valSet = getSet(key);
		valSet->put(val);
	}

	ReadWriteSet<V>* get(K& key) {
		return getSet(key);
	}
};