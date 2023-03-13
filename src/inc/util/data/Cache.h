#pragma once

#include <concepts>

template <typename K, typename V>
	requires std::equality_comparable<K>
class Cache {
public:
	virtual void put(const K &key, V &val) = 0;
	virtual V* get(const K& key) = 0;
	virtual V* remove(const K& key) = 0;
};