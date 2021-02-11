#include "World.h"

World::World()  : m_chunkManager(this)
{
	//IBlock grass;
	//m_blockRegistry.addToRegistry(grass, "grass");
}

void World::setPlayerCam(Camera* cam)
{
	playerCamera = cam;
	init();
}

void World::init()
{
	isRunning = true;
	for (int i = 0; i < 2; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		m_loadThreads.emplace_back([&]()
			{
				while (isRunning)
				{
					loadChunksThread(*playerCamera);
				}
			});
	}
}

void World::addObject(vn::GameObject& obj)
{
	
}

void World::update(float dt)
{
	
}

void World::renderWorld(Renderer& render)
{
	m_chunkManager.getRenderChunks(*playerCamera, m_renderlist);
	for (auto& chunk : m_renderlist)
	{
		chunk->renderChunk(render);
	}
	m_renderlist.clear();
}

void World::setBlock(Block& block, vn::vec3i pos)
{

}

Block& World::getBlock(vn::vec3i pos)
{
	if (/*pos.x > 255 || pos.x < 0 ||*/ (pos.y > 255) || (pos.y < 0) /*|| pos.z > 255 || pos.z < 0*/)
	{
		return Block();
	}

	vn::vec3i blockcoord = vn::vec3i(abs(pos.x) % 16, abs(pos.y) % 16, abs(pos.z) % 16);
	
	return m_chunkManager.getChunk(vn::vec3i(pos.x / 16, pos.y / 16, pos.z / 16)).getBlock(blockcoord);
}

World::~World()
{
	for (auto& t : m_loadThreads)
	{
		t.join();
	}
}

void World::loadChunksThread(const Camera& cam)
{
	int radius = 10;
	for (int x = (cam.pos.x / 16) - radius; x < (cam.pos.x / 16) + radius; ++x)
	{
		for (int z = (cam.pos.z / 16) - radius; z < (cam.pos.z / 16) + radius; ++z)
		{
			for (int y = 0; y < 16; y++)
			{
				vn::vec3i chunkcoords(x, y, z);

				if (m_mainlock.try_lock())
				{
					m_chunkManager.loadChunk(chunkcoords);
					m_chunkManager.getChunk(chunkcoords).makeMesh();
					m_mainlock.unlock();
				}
			}
		}
	}
}

