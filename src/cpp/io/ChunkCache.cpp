#include <io/ChunkCache.h>

ChunkCache::ChunkCache(WorldGenerator &generator) : ObjectPool(new ChunkLoader(&generator)) {

}