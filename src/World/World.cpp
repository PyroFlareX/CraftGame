#include "World.h"

World::World() 
{
	Chunk c;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 16; ++y)
		{
			for (int z = 0; z < 16; ++z)
			{
				m_chunks[vn::vec3i(x, y, z)] = c;
			}
		}
	}
	
}

void World::addObject(vn::GameObject& obj)
{
	
}

void World::update(float dt)
{

}

void World::setBlock(Block& block, vn::vec3i pos)
{
}

Block& World::getBlock(vn::vec3i pos)
{
	// TODO: insert return statement here
	vn::vec3i blockcoord = vn::vec3i(pos.x % 16, pos.y % 16, pos.z % 16);
	return m_chunks.at(vn::vec3i(pos.x / 16, pos.y / 16, pos.z / 16)).getBlock(blockcoord);
}

World::~World()
{
	
}

