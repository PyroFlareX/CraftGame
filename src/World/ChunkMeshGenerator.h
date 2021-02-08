#pragma once

#include "../Model.h"

#include "Chunk.h"
#include "ChunkMesh.h"

#include "../../Engine/Registries/ResourceManager.h"

class ChunkMeshGenerator
{
public:
	ChunkMeshGenerator(Chunk& chunk, ChunkMesh& mesh);

	void makeMesh();
private:

	void tryAddFaceToMesh(	const std::array<GLfloat, 12>& blockFace, const std::string& texName,
							const vn::vec3i& blockPosition, const vn::vec3i& blockFacing);
	bool shouldMakeFace(const vn::vec3i& adjPos);


	Chunk* m_pChunk = nullptr;
	ChunkMesh* m_pChunkMesh = nullptr;
};