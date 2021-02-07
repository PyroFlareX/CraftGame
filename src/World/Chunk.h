#pragma once

#include <array>

#include "Block.h"

constexpr uint16_t CHUNK_SIZE = 16 * 16 * 16;

constexpr int convertPosition(vn::vec3i pos) 
{
	return ((pos.x) + (16 * pos.y) + (256 * pos.z));
}


class Chunk
{
public:
	Chunk();

	Block& getBlock(vn::vec3i& pos);
	void setBlock(vn::vec3i& pos, Block& block);

	~Chunk();
private:
	std::array<Block, CHUNK_SIZE> m_blocks;
};