#include <phys/Player.h>

Player::Player(double x, double y, double z) : PhysicalObject(x, y, z), playerCam{ x,y,z } {
	
}

void Player::update(float delTime) {
	updateChunkRenderers();
}

void Player::updateChunkRenderers() {
	World* theWorld = World::the();

	std::set<std::pair<long,long>> chunksToRender = getChunksToRender();

	//Remove the ones that don't need rendering anymore
	for (auto it = renderers.begin(); it != renderers.end(); it++) {
		auto finder = chunksToRender.find(it->first);
		if (finder == chunksToRender.end()) {
			long chunkX = (*finder).first;
			long chunkY = (*finder).second;
			ChunkRenderer* renderer = renderers.at(std::pair<long, long>{chunkX, chunkY});
			renderers.erase(std::pair<long, long>{chunkX, chunkY});
			delete renderer;
			theWorld->getChunkLoader()->removeChunk(chunkX, chunkY);
		}
	}

	//Add chunks that need rendering
	for (auto it = chunksToRender.begin(); it != chunksToRender.end(); it++) {
		auto finder = renderers.find(*it);
		if (finder == renderers.end()) {
			long chunkX = (*it).first;
			long chunkY = (*it).second;
			Chunk* chunk = theWorld->getChunkLoader()->getChunk(chunkX, chunkY);
			ChunkRenderer* renderer = new ChunkRenderer(chunk);
			renderers.insert({ std::pair<long, long>{chunkX, chunkY}, renderer });
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

void Player::processKeyEvent(int key, int scanCode, int action, int mods) {
	playerCam.processKeyEvent(key, scanCode, action, mods);
}
void Player::processMouseEvent(double xPos, double yPos) {
	playerCam.processMouseEvent(xPos, yPos);
}

void Player::render() {
	for (auto it = renderers.begin(); it != renderers.end(); it++) {
		(*it).second->render();
	}
}