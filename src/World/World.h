#pragma once

#include "../../Engine/Engine.h"

#include "Chunk.h"
#include "ChunkMeshGenerator.h"

#include <unordered_map>

class World
{
public:
	World();
	
	void addObject(vn::GameObject& obj);

	void update(float dt);

	void setBlock(Block& block, vn::vec3i pos);
	Block& getBlock(vn::vec3i pos);

	World(const World& world) = delete;

	~World();
private:
	std::unordered_map<vn::vec3i, Chunk> m_chunks;
};