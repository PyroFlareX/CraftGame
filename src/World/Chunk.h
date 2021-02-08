#pragma once

#include <array>

#include "Block.h"

#include "ChunkMesh.h"
#include "../Renderers/Renderer.h"

constexpr uint16_t CHUNK_SIZE = 16 * 16 * 16;

constexpr int convertPosition(vn::vec3i pos) 
{
	return ((pos.x) + (16 * pos.y) + (256 * pos.z));
}

class World;

class Chunk
{
public:
	Chunk() = default;
	Chunk(World* world, vn::vec3i pos);

	void makeMesh();

	Block& getBlock(const vn::vec3i& pos);
	void setBlock(vn::vec3i& pos, Block& block);

	vn::vec3i getPosition() const;

	void renderChunk(Renderer& render);

	~Chunk();
private:
	bool outOfBounds(int value) const;
	vn::vec3i toWorldPos(int x, int y, int z) const;

	std::array<Block, CHUNK_SIZE> m_blocks;

	ChunkMesh m_Mesh;
	World* m_pWorld;
	vn::vec3i position;

	bool hasMesh = false;
	bool hasBufferedMesh = false;
};