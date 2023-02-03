#include <phys/Player.h>

Player::Player(double x, double y, double z) : PhysicalObject(x, y, z), playerCam{ x,y,z } {
	
}

void Player::update(float delTime) {
	updateChunkRenderers();
}

void Player::updateChunkRenderers() {
	std::set<std::pair<long,long>> chunksToRender = getChunksToRender();

	//Remove the ones that don't need rendering anymore
	for (auto it = renderers.begin(); it != renderers.end(); it++) {
		auto finder = chunksToRender.find(it->first);
		if (finder == chunksToRender.end()) {
			//TODO - Use the chunk loader class to remove this chunk from memory
		}
	}

	//Add chunks that need rendering
	for (auto it = chunksToRender.begin(); it != chunksToRender.end(); it++) {
		auto finder = renderers.find(*it);
		if (finder == renderers.end()) {
			//TODO - Use the chunk loader class to load this chunk into memory, and then create a renderer for it
		}
	}
}

std::set<std::pair<long, long>> Player::getChunksToRender() {
	std::set<std::pair<long, long>> retval{};

	std::pair<long, long> chunkCoord{ floorl(x / Chunk::CHUNK_SIZE), floorl(y / Chunk::CHUNK_SIZE) };
	for (int i = 0; i < renderDistance; i++) {
		for (int j = 0; j < renderDistance; j++) {
			if (i * i + j * j <= renderDistance * renderDistance) {
				retval.insert(std::pair<int, int>{chunkCoord.first + i, chunkCoord.second + i});
			}
		}
	}
	return retval;
}