#pragma once

#include "Chunk.h"

#include <unordered_map>

class World;

class ChunkManager
{
public:
	ChunkManager(World* world);

	void loadChunk(vn::vec3i pos);
	void unloadChunk(vn::vec3i pos);

	Chunk& getChunk(vn::vec3i position);

	void getRenderChunks(Camera& cam, std::vector<Chunk*>& renderChunks);

	//~ChunkManager();
private:
	std::unordered_map<vn::vec3i, Chunk> m_chunks;
	World* m_pWorld;

	bool chunkExists(vn::vec3i position);

	unsigned int noiseHeight(unsigned int x, unsigned int z);
};