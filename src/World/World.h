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


	// Add a Gameobject to the world, pretty much pointless atm, will be used in the future for entities/mobs
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

	//vn::Registry<IBlock> m_blockRegistry;
	//vn::Registry<IBlock> m_blockRegistry;

	ChunkManager m_chunkManager;

	std::vector<Chunk*> m_renderlist;

	std::vector<std::thread> m_loadThreads;
	std::mutex m_mainlock;


	Camera* playerCamera;
};