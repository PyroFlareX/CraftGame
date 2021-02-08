#pragma once

#include "../../Engine/Engine.h"
#include "../Model.h"

class ChunkMesh
{
public:
	void addFace(	const std::array<float, 12>& blockFace, 
					const std::array<float, 8>& texCoords, 
					const vn::vec3i& chunkPos,
					const vn::vec3i& blockPos);

	Model& getModel();
	
	void bufferMesh();

	void deleteData();

	int faces = 0;

private:
	Model m_model;
	vn::Mesh m_mesh;

	unsigned int m_index = 0;
};