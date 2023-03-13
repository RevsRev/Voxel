#pragma once

#include <io/Cache.h>
#include <io/ReadWriteCache.h>
#include <map>
#include <io/ReadWriteSet.h>
#include <shared_mutex>

template <typename K, typename V>
class MultiValCache {
private:
	mutable std::shared_mutex mutex{};
	ReadWriteCache<K, std::pair<long,long>> cache{};

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
		theSet = cache.get(key);

		//check that there wasn't two threads competing for the unique lock
		if (theSet != nullptr) {
			return theSet;
		}
		theSet = ReadWriteSet<V>{};
		cache.put(key, theSet);
		return &cache.get(key);
	}

public:
	void put(const K& key, const V& val) {
		ReadWriteSet<V>* valSet = getSet(key);
		valSet->put(val);
	}

	ReadWriteSet<V*>* get(const K& key) {
		return getSet(key);
	}
};