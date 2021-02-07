#pragma once

#include "../Model.h"
#include "Chunk.h"

class World;

class ChunkMeshGenerator
{
public:
	ChunkMeshGenerator(World* world);

	void makeMesh(Chunk* chunk);
private:
	World* m_world;
};