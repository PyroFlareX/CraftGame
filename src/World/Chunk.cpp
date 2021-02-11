#include "Chunk.h"

#include "ChunkMeshGenerator.h"
#include "World.h"


Chunk::Chunk(World* world, vn::vec3i pos)
{
	std::cout << "Chunk Constructor" << std::endl;
	m_pWorld = world;
	position = pos;

}

void Chunk::makeMesh()
{
	if (!hasMesh)
	{
		ChunkMeshGenerator(*this, m_Mesh).makeMesh();
		hasMesh = true;
		hasBufferedMesh = false;
	}
}

bool Chunk::tryBuffer()
{
	
	if (!hasBufferedMesh && hasMesh)
	{
		m_Mesh.bufferMesh();
		hasBufferedMesh = true;
		return true;
	}
	else
	{
		///
		return false;
	}
	return false;
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
	tryBuffer();
	if (hasBufferedMesh)
	{
		render.drawChunk(m_Mesh);
	}
}

Chunk::~Chunk()
{

}

bool Chunk::outOfBounds(int value) const
{
	return ((value > 15) || (value < 0));
}

vn::vec3i Chunk::toWorldPos(int x, int y, int z) const
{
	return vn::vec3i(position.x * 16 + x, position.y * 16 + y, position.z * 16 + z);
}
