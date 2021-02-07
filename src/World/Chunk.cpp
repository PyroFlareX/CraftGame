#include "Chunk.h"

Chunk::Chunk()
{
	Block b;
	b.id = 0;
	for (int x = 0; x < 16; ++x)
	{
		for (int y = 0; y < 16; ++y)
		{
			for (int z = 0; z < 16; ++z)
			{
				m_blocks[convertPosition(vn::vec3i(x, y, z)) ] = b;
			}
		}
	}

}

Block& Chunk::getBlock(vn::vec3i& pos)
{
	// TODO: insert return statement here
	return m_blocks[convertPosition(pos)];
}

void Chunk::setBlock(vn::vec3i& pos, Block& block)
{

}

Chunk::~Chunk()
{

}
