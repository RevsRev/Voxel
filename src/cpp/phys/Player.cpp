#include <phys/Player.h>

Player::Player(double x, double y, double z) : PhysicalObject(x, y, z), playerCam{ x,y,z } {
	this->lastChunkCacheX = x;
	this->lastChunkCacheY = y;
	this->lastChunkCacheZ = z;
}

void Player::update(float delTime) {

	bool updateRenderers = updateChunkPosition();
	if (updateRenderers) {
		updateChunkRenderers();
	}
}

//TODO - Replace with player's position, not the cameras
bool Player::updateChunkPosition() {
	long newChunkX = playerCam.x / Chunk::CHUNK_SIZE;
	long newChunkY = playerCam.y / Chunk::CHUNK_SIZE;

	if (newChunkX == chunkX && newChunkY == chunkY) {
		return false;
	}
	chunkX = newChunkX;
	chunkY = newChunkY;
	return true;
}

void Player::updateChunkRenderers() {
	World* theWorld = World::the();

	std::set<std::pair<long, long>> chunksToDelete = getChunksToDelete();
	std::map<std::pair<long, long>, std::future<Chunk*>*> newChunks{};

	//Remove the ones that don't need rendering anymore
	for (auto it = chunksToDelete.begin(); it != chunksToDelete.end(); it++) {
		long chunkX = it->first;
		long chunkY = it->second;
		std::pair<long, long> key{ chunkX, chunkY };
		if (renderers.find(key) != renderers.end()) {
			deleteChunkAsync(chunkX, chunkY);
			ChunkRenderer* renderer = renderers.at(key);
			renderers.erase(key);
			delete renderer;
		}
	}

	//Load the chunks that need rendering
	std::set<std::pair<long, long>> chunksToRender = getChunksToRender();
	for (auto it = chunksToRender.begin(); it != chunksToRender.end(); it++) {
		auto finder = renderers.find(*it);
		if (finder == renderers.end()) {
			long chunkX = (*it).first;
			long chunkY = (*it).second;
			std::pair<long, long> key{ chunkX, chunkY };
			newChunks.insert({ key, getChunkAsync(chunkX, chunkY) });
		}
	}

	//crate the new renderers
	for (auto it = newChunks.begin(); it != newChunks.end(); it++) {
		std::pair<long, long> key = (*it).first;
		renderers.insert({ key, new ChunkRenderer(getChunk(key.first, key.second)) });
	}

	lastChunkCacheX = playerCam.x;
	lastChunkCacheY = playerCam.y;
}

std::future<Chunk*>* Player::getChunkAsync(long &chunkX, long &chunkY) {
	return &std::async(std::launch::async, &ChunkLoader::getChunk, World::the()->getChunkLoader(), std::ref(chunkX), std::ref(chunkY));
}
Chunk* Player::getChunk(long &chunkX, long &chunkY) {
	World* theWorld = World::the();
	return theWorld->getChunkLoader()->getChunk(chunkX, chunkY);
}

std::future<void>* Player::deleteChunkAsync(long &chunkX, long &chunkY) {
	return &std::async(std::launch::async, &ChunkLoader::removeChunk, World::the()->getChunkLoader(), std::ref(chunkX), std::ref(chunkY));
}

//TODO - Replace with the palyer's position and update the player
std::set<std::pair<long, long>> Player::getChunksToRender() {

	long chunkX = floorl(playerCam.x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(playerCam.y / Chunk::CHUNK_SIZE);
	std::set<std::pair<long, long>> retval{};

	long squaredRad = renderDistance * renderDistance;

	if (firstChunkCache) {
		for (int i = -renderDistance; i <= renderDistance; i++) {
			for (int j = -renderDistance; j <= renderDistance; j++) {
				if (i * i + j * j <= squaredRad) {
					retval.insert(std::pair<int, int>{chunkX + i, chunkY + j});
				}
			}
		}
		firstChunkCache = false;
		return retval;
	}

	long lastChunkX = floorl(lastChunkCacheX / Chunk::CHUNK_SIZE);
	long lastChunkY = floorl(lastChunkCacheY / Chunk::Chunk::CHUNK_SIZE);
	long squaredRadWithSlack = (renderDistance - 2) * (renderDistance - 2);

	for (int i = chunkX - renderDistance; i <= chunkX + renderDistance; i++) {
		for (int j = chunkY - renderDistance; j <= chunkY + renderDistance; j++) {
			if (((i - chunkX) * (i - chunkX) + (j - chunkY) * (j - chunkY) <= squaredRad)
				&& ((i - lastChunkX) * (i - lastChunkX) + (j - lastChunkY) * (j - lastChunkY) > squaredRadWithSlack)) {
				retval.insert(std::pair<int, int>{i,j});
			}
		}
	}
	return retval;
}

std::set<std::pair<long, long>> Player::getChunksToDelete() {
	std::set<std::pair<long, long>> retval{};
	if (firstChunkCache) {
		return retval;
	}
	long chunkX = floorl(playerCam.x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(playerCam.y / Chunk::CHUNK_SIZE);
	long lastChunkX = floorl(lastChunkCacheX / Chunk::CHUNK_SIZE);
	long lastChunkY = floorl(lastChunkCacheY / Chunk::Chunk::CHUNK_SIZE);
	long squaredRad = renderDistance * renderDistance;
	long squaredRadWithSlack = (renderDistance + 2) * (renderDistance + 2);
	long checkDistance = std::ceill(std::fmax(std::abs(chunkX - lastChunkX) + renderDistance + 1, std::abs(chunkY - lastChunkY) + renderDistance + 1));
	long squredCheckDistance = checkDistance * checkDistance;

	for (int i = chunkX - checkDistance; i <= chunkX + checkDistance; i++) {
		for (int j = chunkY - checkDistance; j <= chunkY + checkDistance; j++) {
			if (((i - chunkX) * (i - chunkX) + (j - chunkY) * (j - chunkY) > squaredRad)
				&& ((i - lastChunkX) * (i - lastChunkX) + (j - lastChunkY) * (j - lastChunkY) <= squaredRadWithSlack)) {
				retval.insert(std::pair<int, int>{i, j});
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
	glm::mat4 view = playerCam.getView();
	glm::vec3 position = playerCam.getPosition();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 800.0f);
	glm::vec3 lightDirection = glm::normalize(glm::vec3{ 0.0f, 0.5f, 1.0f });

	for (auto it = renderers.begin(); it != renderers.end(); it++) {
		ChunkRenderer* renderer = (*it).second;

		int modelLoc = renderer->getShaderProgram()->getUniformLocation("model");
		int viewLoc = renderer->getShaderProgram()->getUniformLocation("view");
		int projLoc = renderer->getShaderProgram()->getUniformLocation("projection");
		int lightDirLoc = renderer->getShaderProgram()->getUniformLocation("lightDirection");
		int camPosLoc = renderer->getShaderProgram()->getUniformLocation("cameraPosition");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDirection));
		glUniform3fv(lightDirLoc, 1, &lightDirection[0]);
		glUniform3fv(camPosLoc, 1, &(position)[0]);

		renderer->render();
	}
}