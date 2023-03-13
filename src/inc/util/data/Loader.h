#pragma once

#include <struc/Chunk.h>
#include <map>

template <typename K, typename V>
class Loader {
public:
	virtual V& load(K &key, std::map<std::string, std::string> &args) = 0;
};