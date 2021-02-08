#include "World.h"

World::World()  : m_chunkManager(this)
{
	
	
	
}

void World::setPlayerCam(Camera* cam)
{
	playerCamera = cam;
}

void World::addObject(vn::GameObject& obj)
{
	
}

void World::update(float dt)
{
	
}

void World::renderWorld(Renderer& render)
{
	int rad = 5;
	
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
	if (pos.x > 255 || pos.x < 0 || pos.y > 255 || pos.y < 0 || pos.z > 255 || pos.z < 0)
	{
		return Block();
	}

	vn::vec3i blockcoord = vn::vec3i(pos.x % 16, pos.y % 16, pos.z % 16);
	
	return m_chunkManager.getChunk(vn::vec3i(pos.x / 16, pos.y / 16, pos.z / 16)).getBlock(blockcoord);
}

World::~World()
{
	
}

