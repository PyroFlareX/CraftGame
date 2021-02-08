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

	Block dirt;
	dirt.id = 1;

	for (int x = pos.x * 16; x < pos.x * 16 + 16; ++x)
	{
		for (int z = pos.z * 16; z < pos.z * 16 + 16; ++z)
		{
			unsigned int height = noiseHeight(x, z);
			for (int y = pos.y * 16; y < pos.y * 16 + 16; ++y)
			{
				vn::vec3i blockcoords(x % 16, y % 16, z % 16);
				if (height < (y))
				{
					c.setBlock(blockcoords, air);
				}
				else
				{
					c.setBlock(blockcoords, dirt);
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
	int radius = 3;
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

unsigned int ChunkManager::noiseHeight(unsigned int x, unsigned int z)
{
	float height = glm::simplex(glm::vec2(x / 16.0f, z / 16.0f));

	height = (height + 1.0f) / 2.0f;

	height *= 6;

	return height;
}
