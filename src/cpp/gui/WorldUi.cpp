#include <gui/WorldUi.h>

WorldUi::WorldUi(World* world) : pool{ world->getChunkLoader() } {
	this->world = world;
	pool.addSubscriber(this);
}

void WorldUi::addCamera(Camera* camera) {
	if (cameras.find(camera) == cameras.end()) {
		cameras.insert(camera);
	}
}

void WorldUi::setSelectedCamera(Camera* camera) {
	addCamera(camera);
	selectedCamera = camera;

	glm::vec3 position = camera->getPosition();
	this->lastChunkCacheX = position.x;
	this->lastChunkCacheY = position.y;
	this->lastChunkCacheZ = position.z;

}

void WorldUi::update(float delTime) {
	bool updateRenderers = updateChunkPosition();
	if (updateRenderers) {
		updateChunkRenderers();
	}
}

bool WorldUi::updateChunkPosition() {
	long newChunkX = selectedCamera->getPosition().x / Chunk::CHUNK_SIZE;
	long newChunkY = selectedCamera->getPosition().y / Chunk::CHUNK_SIZE;

	if (newChunkX == chunkX && newChunkY == chunkY) {
		return false;
	}
	chunkX = newChunkX;
	chunkY = newChunkY;
	return true;
}

void WorldUi::updateChunkRenderers() {
	World* theWorld = World::the();

	std::set<std::pair<long, long>> chunksToDelete = getChunksToDelete();
	std::map<std::pair<long, long>, std::future<Chunk*>*> newChunks{};

	//Remove the ones that don't need rendering anymore
	for (auto it = chunksToDelete.begin(); it != chunksToDelete.end(); it++) {
		long chunkX = it->first;
		long chunkY = it->second;
		std::pair<long, long> key{ chunkX, chunkY };
		if (renderers.find(key) != renderers.end()) {
			//deleteChunkAsync(chunkX, chunkY);
			//ChunkRenderer* renderer = renderers.at(key);
			//renderers.erase(key);
			//delete renderer;
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
			pool.asyncRequest(this, key, std::map<std::string, std::string >{});
			//newChunks.insert({ key, getChunkAsync(chunkX, chunkY) });

			//just for testing
			//pool.asyncRequest(this,key, std::map<std::string,std::string>{});

		}
	}

	//crate the new renderers
	for (auto it = newChunks.begin(); it != newChunks.end(); it++) {
		std::pair<long, long> key = (*it).first;
		renderers.insert({ key, new ChunkRenderer(getChunk(key.first, key.second)) });
	}

	lastChunkCacheX = selectedCamera->getPosition().x;
	lastChunkCacheY = selectedCamera->getPosition().y;
}

std::future<Chunk*>* WorldUi::getChunkAsync(long& chunkX, long& chunkY) {
	return &std::async(std::launch::async, &ChunkLoader::getChunk, World::the()->getChunkLoader(), std::ref(chunkX), std::ref(chunkY));
}
Chunk* WorldUi::getChunk(long& chunkX, long& chunkY) {
	World* theWorld = World::the();
	return theWorld->getChunkLoader()->getChunk(chunkX, chunkY);
}

std::future<void>* WorldUi::deleteChunkAsync(long& chunkX, long& chunkY) {
	return &std::async(std::launch::async, &ChunkLoader::removeChunk, World::the()->getChunkLoader(), std::ref(chunkX), std::ref(chunkY));
}

//TODO - Replace with the palyer's position and update the player
std::set<std::pair<long, long>> WorldUi::getChunksToRender() {

	long chunkX = floorl(selectedCamera->getPosition().x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(selectedCamera->getPosition().y / Chunk::CHUNK_SIZE);
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
				retval.insert(std::pair<int, int>{i, j});
			}
		}
	}
	return retval;
}

std::set<std::pair<long, long>> WorldUi::getChunksToDelete() {
	std::set<std::pair<long, long>> retval{};
	if (firstChunkCache) {
		return retval;
	}
	long chunkX = floorl(selectedCamera->getPosition().x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(selectedCamera->getPosition().y / Chunk::CHUNK_SIZE);
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



void WorldUi::render() {
	glm::mat4 view = selectedCamera->getView();
	glm::vec3 position = selectedCamera->getPosition();
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

bool WorldUi::checkRenderDistance(long& chunkX, long& chunkY) {
	return (lastChunkCacheX - chunkX) * (lastChunkCacheX - chunkX) + (lastChunkCacheY - chunkY) * (lastChunkCacheY - chunkY) < renderDistance * renderDistance;
}

void WorldUi::onCreate(Chunk& val) {
	std::pair<long, long>key{ val.getChunkX(), val.getChunkY() };
	renderers.insert({ key, new ChunkRenderer(&val)});
}
void WorldUi::onUpdate(Chunk& val) {
	//TODO - implement at a later date
}
void WorldUi::onDelete(Chunk& val) {
	//TODO - implement at a later date
}