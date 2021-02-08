#include "ChunkMesh.h"

void ChunkMesh::addFace(const std::array<GLfloat, 12>& blockFace, const std::array<GLfloat, 8>& texCoords, const vn::vec3i & chunkPos, const vn::vec3i & blockPos)
{
	//faces++;

	/*texCoords.insert(texCoords.end(), textureCoords.begin(),
		textureCoords.end());*/
	
	vn::Vertex v;
	
	/// Vertex: The current vertex in the "blockFace" vector, 4 vertex in total
	/// hence "< 4" Index: X, Y, Z
	for (int i = 0, index = 0, texIndex = 0; i < 4; ++i) {
		
		v.position = vn::vec3(blockFace[index++] + chunkPos.x * 16 +
			blockPos.x, blockFace[index++] + chunkPos.y * 16 +
			blockPos.y, blockFace[index++] + chunkPos.z * 16 +
			blockPos.z);
		//v.normal = vn::vec3(0.0f, 0.0f, 0.0f);
		v.uv = vn::vec2(texCoords[texIndex++], texCoords[texIndex++]);
		
		m_mesh.vertices.push_back(v);
	}

	m_mesh.indicies.insert(m_mesh.indicies.end(),
		{ m_index + 2, m_index + 1, m_index,

		 m_index, m_index + 3, m_index + 2 });
	m_index += 4;
}

Model& ChunkMesh::getModel()
{
	return m_model;
}

void ChunkMesh::bufferMesh()
{
	m_model.addData(m_mesh);

	m_mesh.vertices.clear();
	m_mesh.indicies.clear();

	m_mesh.vertices.shrink_to_fit();
	m_mesh.indicies.shrink_to_fit();

	m_index = 0;
}

void ChunkMesh::deleteData()
{
	m_model.deleteData();
}
