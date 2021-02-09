#include "ChunkManager.h"

#include <glm/gtc/noise.hpp>

ChunkManager::ChunkManager(World* world)
{
	m_pWorld = world;
}

void ChunkManager::loadChunk(vn::vec3i pos)
{
	Chunk c(m_pWorld, pos);
	Block air;
	air.id = 0;

	Block grass;
	grass.id = 1;

	Block dirt;
	dirt.id = 2;

	Block stone;
	stone.id = 4;

	//Done like this instead of scaled per chunk for a) a workaround due to a modulo bug
	// and b) for a possible performance improvement?
	for (int x = 0; x <  16; ++x)
	{
		for (int z = 0; z < 16; ++z)
		{
			// height : the y height of the surface layer at a given world (x,z) coordinate given by a simplex noise algorithm
			unsigned int height = noiseHeight(x + pos.x * 16, z + pos.z * 16);
			for (int y = 0; y < 16; ++y)
			{
				
				vn::vec3i blockcoords(x, y, z);
				if (height < (y + (pos.y * 16)))
				{
					c.setBlock(blockcoords, air);
				}
				else if(height > (y + (pos.y * 16)))
				{
					c.setBlock(blockcoords, stone);
				}
				else if (height == (y + (pos.y * 16)))
				{
					c.setBlock(blockcoords, grass);
				}
			}
		}
	}


	m_chunks.emplace(pos, std::move(c));
}

void ChunkManager::unloadChunk(vn::vec3i pos)
{

}

Chunk& ChunkManager::getChunk(vn::vec3i position)
{
	return m_chunks[position];
}

void ChunkManager::getRenderChunks(Camera& cam, std::vector<Chunk*>& renderChunks)
{
	int radius = 6;
	for (int x = (cam.pos.x / 16) - radius; x < (cam.pos.x / 16) + radius; ++x)
	{
		for (int z = (cam.pos.z / 16) - radius; z < (cam.pos.z / 16) + radius; ++z)
		{
			for (int y = 0; y < 16; ++y)
			{
				vn::vec3i chunkcoords(x, y, z);
				if (!chunkExists(chunkcoords))
				{
					loadChunk(chunkcoords);
					std::cout << x << " " << y << " " << z << std::endl;
				}
				
				renderChunks.emplace_back(&m_chunks[chunkcoords]);
			}
		}
	}
}

bool ChunkManager::chunkExists(vn::vec3i position)
{
	return (m_chunks.find(position) != m_chunks.end());
}

unsigned int ChunkManager::noiseHeight(int x, int z)
{
	float height = glm::simplex(glm::vec2(x / 16.0f, z / 16.0f));

	height = (height + 1.1f) / 2.1f;

	height *= 8;

	return height;
}
