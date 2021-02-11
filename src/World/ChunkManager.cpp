#include "ChunkManager.h"

#include <glm/gtc/noise.hpp>

ChunkManager::ChunkManager(World* world)
{
	m_pWorld = world;
}

void ChunkManager::loadChunk(vn::vec3i pos)
{
	/// @TODO : IMPLEMENT CHUNK SAVING STRUCTURE


	Block air;
	air.id = 0;

	Block grass;
	grass.id = 1;

	Block dirt;
	dirt.id = 2;

	Block stone;
	stone.id = 4;
	
	if (!chunkExists(pos))
	{

		Chunk c(m_pWorld, pos);

		//Done like this instead of scaled per chunk for a) a workaround due to a modulo bug
		// and b) for a possible performance improvement?
		for (int x = 0; x < 16; ++x)
		{
			for (int z = 0; z < 16; ++z)
			{
				// height : the y height of the surface layer at a given world (x,z) coordinate given by a simplex noise algorithm
				unsigned int height = noiseHeight(x + (pos.x * 16), z + (pos.z * 16));
				for (int y = 0; y < 16; y++)
				{

					vn::vec3i blockcoords(x, y, z);
					if (height < (y + (pos.y * 16)))
					{
						c.setBlock(blockcoords, air);
					}
					else if (height > (y + (pos.y * 16)))
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
		std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
	}
}

void ChunkManager::unloadChunk(vn::vec3i pos)
{
	/// @TODO : IMPLEMENT CHUNK SAVING TO FILE
	/// IF POSSIBLE THIS FUNCTION SHOULD BE async
}

Chunk& ChunkManager::getChunk(vn::vec3i position)
{
	if (!chunkExists(position))
	{
		loadChunk(position);
	}
	return m_chunks[position];
}

void ChunkManager::getRenderChunks(const Camera& cam, std::vector<Chunk*>& renderChunks)
{
	int radius = 6;
	for (int x = (cam.pos.x / 16) - radius; x < (cam.pos.x / 16) + radius; ++x)
	{
		for (int z = (cam.pos.z / 16) - radius; z < (cam.pos.z / 16) + radius; ++z)
		{
			for (int y = 0; y < 16; y++)
			{
				vn::vec3i chunkcoords(x, y, z);
				if (chunkExists(chunkcoords))
				{
					renderChunks.emplace_back(&m_chunks[chunkcoords]);
				}
			}
		}
	}
}

bool ChunkManager::chunkExists(vn::vec3i position)
{
	std::unique_lock<std::mutex> lock(m_accessLock);
	return (m_chunks.find(position) != m_chunks.end());
}

const unsigned short noiseHeight(int x, int z)
{
	float height = glm::simplex(glm::vec2(x / 64.0f, z / 64.0f));

	height = (height + 1.1f) * 10.0f + 1;

	
	return static_cast<unsigned short>(height);
}
