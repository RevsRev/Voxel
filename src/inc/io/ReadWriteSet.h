#pragma once

#include <set>
#include <shared_mutex>

template <typename V>
class ReadWriteSet {
private:
	std::set<V> set{};
	mutable std::shared_mutex mutex{};

public:
	void put(V &val) {
		std::unique_lock<std::shared_mutex> lock{ mutex };
		set.insert(val);
	}
	bool contains(V &val) {
		std::shared_lock<std::shared_mutex> lock{ mutex };
		return set.find(val) != set.end();
	}
	void remove(V &val) {
		std::unique_lock<std::shared_mutex> lock{ mutex };
		if (set.find(val) != set.end()) {
			set.erase(val);
		}
	}
};