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
	bool flushPool = updateChunkPosition();
	if (flushPool) {
		flushChunkPool();
	}
	flushChunkQueue();
	flushRenderersToDelete();
}

void WorldUi::flushChunkQueue() {
	queueLock.lock();

	for (auto it = chunkQueue.begin(); it != chunkQueue.end(); it++) {
		std::pair<long, long> key = (*it).first;
		Chunk* chunk = (*it).second;
		renderLock.lock();
		renderers.insert({ key, new ChunkRenderer(chunk) });
		renderLock.unlock();
	}
	chunkQueue.clear();
	queueLock.unlock();
}

void WorldUi::flushRenderersToDelete() {
	rendererDeleteLock.lock();

	for (auto it = renderersToDelete.begin(); it != renderersToDelete.end(); it++) {
		ChunkRenderer* renderer = (*it).second;
		delete renderer;
	}
	renderersToDelete.clear();

	rendererDeleteLock.unlock();
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

void WorldUi::flushChunkPool() {

	long chunkX = floorl(selectedCamera->getPosition().x / Chunk::CHUNK_SIZE);
	long chunkY = floorl(selectedCamera->getPosition().y / Chunk::CHUNK_SIZE);
	std::set<std::pair<long, long>> retval{};

	long squaredRad = renderDistance * renderDistance;

	std::map<std::string, std::string> args{};

	if (firstChunkCache) {
		for (int i = -renderDistance; i <= renderDistance; i++) {
			for (int j = -renderDistance; j <= renderDistance; j++) {
				std::pair<long, long> key{ chunkX + i, chunkY + j };
				pool.asyncRequest(this, key, args);
			}
		}
		lastChunkCacheX = selectedCamera->getPosition().x;
		lastChunkCacheY = selectedCamera->getPosition().y;
		firstChunkCache = false;
		return;
	}

	long lastChunkX = floorl(lastChunkCacheX / Chunk::CHUNK_SIZE);
	long lastChunkY = floorl(lastChunkCacheY / Chunk::Chunk::CHUNK_SIZE);
	lastChunkCacheX = selectedCamera->getPosition().x;
	lastChunkCacheY = selectedCamera->getPosition().y;
	long squaredRadWithSlack = (renderDistance - 2) * (renderDistance - 2);

	//circular caching - seemed very slow
	/*int left = chunkX - renderDistance;
	int right = chunkX + renderDistance;
	int bottom = chunkY - renderDistance;
	int top = chunkY + renderDistance;
	for (int i = left; i <= right; i++) {
		for (int j = bottom; j <= top; j++) {
			if (((i - chunkX) * (i - chunkX) + (j - chunkY) * (j - chunkY) <= squaredRad)
				&& ((i - lastChunkX) * (i - lastChunkX) + (j - lastChunkY) * (j - lastChunkY) > squaredRadWithSlack)) {
				std::pair<long, long> key{i, j};
				pool.asyncRequest(this, key, args);
			}
		}
	}*/
  	int lastBottom = lastChunkY - renderDistance;
	int lastTop = lastChunkY + renderDistance;
	int top = chunkY + renderDistance;
	int bottom = chunkY - renderDistance;

	int lastLeft = lastChunkX - renderDistance;
	int lastRight = lastChunkX + renderDistance;
	int left = chunkX - renderDistance;
	int right = chunkX + renderDistance;

	int deleteXleft;
	int deleteXright;
	int addXleft;
	int addXright;
	if (lastLeft < left) {
		deleteXleft = lastLeft;
		deleteXright = left - 1;
		addXleft = lastRight + 1;
		addXright = right;
	}
	else {
		deleteXleft = right + 1;
		deleteXright = lastRight;
		addXleft = left;
		addXright = lastLeft-1;
	}

	//TODO - Combine into one to make more efficient (maybe?)
	for (int j = lastBottom; j <= lastTop; j++) {
		for (int i = deleteXleft; i <= deleteXright; i++) {
			std::pair<long, long> key{ i,j };
			pool.asyncRelease(this, key);
		}
	}
	for (int j = bottom; j <= top; j++) {
		for (int i = addXleft; i <= addXright; i++) {
			std::pair<long, long> key{ i,j };
			pool.asyncRequest(this, key, args);
		}
	}

	int deleteYbottom;
	int deleteYtop;
	int addYbottom;
	int addYtop;
	if (lastBottom < bottom) {
		deleteYbottom = lastBottom;
		deleteYtop = bottom - 1;
		addYbottom = lastTop + 1;
		addYtop = top;
	}
	else {
		deleteYbottom = top + 1;
		deleteYtop = lastTop;
		addYbottom = bottom;
		addYtop = lastBottom - 1;
	}

	//we've already done some of the x values, so we can speed up the process
	int xLeftLimit;
	if (left < lastLeft) {
		xLeftLimit = lastLeft;
	}
	else {
		xLeftLimit = left;
	}
	int xRightLimit;
	if (right < lastRight) {
		xRightLimit = right;
	}
	else {
		xRightLimit = lastRight;
	}

	for (int i = xLeftLimit; i <= xRightLimit; i++) {
		for (int j = deleteYbottom; j <= deleteYtop; j++) {
			std::pair<long, long> key{ i,j };
			pool.asyncRelease(this, key);
		}
		for (int j = addYbottom; j <= addYtop; j++) {
			std::pair<long, long> key{ i,j };
			pool.asyncRequest(this, key, args);
		}
	}
}

Chunk* WorldUi::getChunk(long& chunkX, long& chunkY) {
	World* theWorld = World::the();
	return theWorld->getChunkLoader()->getChunk(chunkX, chunkY);
}

void WorldUi::render() {
	glm::mat4 view = selectedCamera->getView();
	glm::vec3 position = selectedCamera->getPosition();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 800.0f);
	glm::vec3 lightDirection = glm::normalize(glm::vec3{ 0.0f, 0.5f, 1.0f });

	renderLock.lock();

	for (auto it = renderers.begin(); it != renderers.end(); it++) {
		std::pair<long, long> key = (*it).first;
		ChunkRenderer* renderer = (*it).second;
		//std::cout << "key = (" << key.first << "," << key.second << ")" << std::endl;

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

	renderLock.unlock();
}

bool WorldUi::checkRenderDistance(long& chunkX, long& chunkY) {
	return (lastChunkCacheX - chunkX) * (lastChunkCacheX - chunkX) + (lastChunkCacheY - chunkY) * (lastChunkCacheY - chunkY) < renderDistance * renderDistance;
}

void WorldUi::onCreate(Chunk& val) {
	val.cacheVoxelData();
	std::pair<long, long>key{ val.getChunkX(), val.getChunkY() };
	queueLock.lock();
	chunkQueue.insert({ key, &val});
	queueLock.unlock();
}
void WorldUi::onUpdate(Chunk& val) {
	//TODO - implement at a later date
}
void WorldUi::onDelete(Chunk& val) {
	std::pair<long, long>key{ val.getChunkX(), val.getChunkY() };
	renderLock.lock();
	queueLock.lock();
	rendererDeleteLock.lock();

	if (chunkQueue.find(key) != chunkQueue.end()) {
		chunkQueue.erase(key);
	}

	if (renderers.find(key) != renderers.end()) {
		ChunkRenderer* renderer = renderers.at(key);
		renderers.erase(key);
		renderersToDelete.insert({ key, renderer });
	}

	rendererDeleteLock.unlock();
	queueLock.unlock();
	renderLock.unlock();
}