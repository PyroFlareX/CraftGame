#include "Chunk.h"

#include "ChunkMeshGenerator.h"
#include "World.h"


Chunk::Chunk(World* world, vn::vec3i pos)
{
	m_pWorld = world;
	position = pos;
	Block b;
	b.id = 1;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 10; ++y)
		{
			for (int z = 0; z < 16; ++z)
			{
				if (outOfBounds(position.x) || outOfBounds(position.y) || outOfBounds(position.z))
				{
					m_blocks[convertPosition(vn::vec3i(x, y, z))] = Block();
				}
				else
				{
					m_blocks[convertPosition(vn::vec3i(x, y, z))] = b;
				}
			}
		}
		for (int y = 10; y < 16; ++y)
		{
			for (int z = 0; z < 16; ++z)
			{
				if (outOfBounds(position.x) || outOfBounds(position.y) || outOfBounds(position.z))
				{
					m_blocks[convertPosition(vn::vec3i(x, y, z))] = Block();
				}
				else
				{
					m_blocks[convertPosition(vn::vec3i(x, y, z))] = Block();
				}
			}
		}
	}

	m_blocks[convertPosition(vn::vec3i(5, 5, 5))] = Block();

}

void Chunk::makeMesh()
{
	ChunkMeshGenerator(*this, m_Mesh).makeMesh();
	hasMesh = true;
	hasBufferedMesh = false;
	
}

Block& Chunk::getBlock(const vn::vec3i& pos)
{
	if (outOfBounds(pos.x) || outOfBounds(pos.y) || outOfBounds(pos.z))
	{
		auto location = toWorldPos(pos.x, pos.y, pos.z);
		return m_pWorld->getBlock(location);
	}
	return m_blocks[convertPosition(pos)];
}

void Chunk::setBlock(vn::vec3i& pos, Block& block)
{
	m_blocks[convertPosition(pos)] = block;
}

vn::vec3i Chunk::getPosition() const
{
	return position;
}

void Chunk::renderChunk(Renderer& render)
{
	if (!hasMesh)
	{
		makeMesh();
		m_Mesh.bufferMesh();
	}
	render.drawChunk(m_Mesh);
}

Chunk::~Chunk()
{

}

bool Chunk::outOfBounds(int value) const
{
	return (value > 15 || value < 0);
}

vn::vec3i Chunk::toWorldPos(int x, int y, int z) const
{
	return vn::vec3i(position.x * 16 + x, position.y * 16 + y, position.z * 16 + z);
}
