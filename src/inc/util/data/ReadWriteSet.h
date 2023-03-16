#pragma once

#include <set>
#include <shared_mutex>

template <typename V>
class ReadWriteSet {
private:
	std::set<V> set{};
	mutable std::shared_mutex mutex{};

public:
	void put(V val) {
		//std::unique_lock<std::shared_mutex> lock{ mutex };
		mutex.lock();
		set.insert(val);
		mutex.unlock();
	}
	bool contains(V &val) {
		//std::shared_lock<std::shared_mutex> lock{ mutex };
		mutex.lock_shared();
		return set.find(val) != set.end();
		mutex.unlock_shared();
	}
	void remove(V &val) {
		//std::unique_lock<std::shared_mutex> lock{ mutex };
		mutex.lock();
		if (set.find(val) != set.end()) {
			set.erase(val);
		}
		mutex.unlock();
	}

	ReadWriteSet() {

	}
	ReadWriteSet(const ReadWriteSet& readWriteSet) {
		//TODO - might want to implement this properly at some point.
	}
};