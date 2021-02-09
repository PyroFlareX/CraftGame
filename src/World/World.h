#pragma once

#include "../../Engine/Engine.h"

#include "Chunk.h"
#include "ChunkMeshGenerator.h"

#include "ChunkManager.h"

#include <thread>

class Camera;

class World
{
public:
	World();
	
	void setPlayerCam(Camera* cam);

	void init();

	void addObject(vn::GameObject& obj);

	void update(float dt);

	void renderWorld(Renderer& render);

	void setBlock(Block& block, vn::vec3i pos);
	Block& getBlock(vn::vec3i pos);

	World(const World& world) = delete;

	bool isRunning = false;

	~World();
private:
	void loadChunksThread(const Camera& cam);

	ChunkManager m_chunkManager;

	std::vector<Chunk*> m_renderlist;

	std::vector<std::thread> m_loadThreads;


	Camera* playerCamera;
};