#pragma once

template <typename K, typename V>
class Cache {
public:
	virtual void put(const K &key, const V &val) = 0;
	virtual V* get(const K& key) = 0;
	virtual V* remove(const K& key) = 0;
};