#include <phys/Player.h>

Player::Player(double x, double y, double z) : PhysicalObject(x, y, z), playerCam{ x,y,z } {
	
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

	std::set<std::pair<long,long>> chunksToRender = getChunksToRender();

	//Remove the ones that don't need rendering anymore
	for (auto it = renderers.begin(); it != renderers.end();) {
		auto finder = chunksToRender.find(it->first);
		long chunkX = (*it).first.first;
		long chunkY = (*it).first.second;
		it++; //Increment here so that we don't delete the element the iterator points at
		if (finder == chunksToRender.end()) {
			ChunkRenderer* renderer = renderers.at(std::pair<long, long>{chunkX, chunkY});
			//TODO - Fix
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

//TODO - Replace with the palyer's position and update the player
std::set<std::pair<long, long>> Player::getChunksToRender() {
	std::set<std::pair<long, long>> retval{};

	/*long chunkX = floorl(x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(y / Chunk::CHUNK_SIZE);*/
	long chunkX = floorl(playerCam.x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(playerCam.y / Chunk::CHUNK_SIZE);

	for (int i = -renderDistance; i <= renderDistance; i++) {
		for (int j = -renderDistance; j <= renderDistance; j++) {
			if (i * i + j * j <= renderDistance * renderDistance) {
				retval.insert(std::pair<int, int>{chunkX + i, chunkY + j});
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