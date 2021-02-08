#include "ChunkMeshGenerator.h"

const std::array<GLfloat, 12> frontFace {
	0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
};

const std::array<GLfloat, 12> backFace {
	1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
};

const std::array<GLfloat, 12> leftFace {
	0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
};

const std::array<GLfloat, 12> rightFace {
	1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
};

const std::array<GLfloat, 12> topFace {
	0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
};

const std::array<GLfloat, 12> bottomFace { 
	0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 
};

struct AdjacentBlockPositions {
	void update(int x, int y, int z)
	{
		up = { x, y + 1, z };
		down = { x, y - 1, z };
		left = { x - 1, y, z };
		right = { x + 1, y, z };
		front = { x, y, z + 1 };
		back = { x, y, z - 1 };
	}

	vn::vec3i up;
	vn::vec3i down;
	vn::vec3i left;
	vn::vec3i right;
	vn::vec3i front;
	vn::vec3i back;
};

int faces;



ChunkMeshGenerator::ChunkMeshGenerator(Chunk& chunk, ChunkMesh& mesh)
{
	m_pChunk = &chunk;
	m_pChunkMesh = &mesh;
}

void ChunkMeshGenerator::makeMesh()
{
	AdjacentBlockPositions directions;
	faces = 0;

	//Loop through each block in the chunk
	//Check each side of the block, and if the side is exposed, add the face to the mesh
	for (int i = 0; i < 16 * 16 * 16; ++i)
	{
		int x = i % 16;
		int y = i / (16 * 16);
		int z = (i / 16) % 16;

		auto position = vn::vec3i(x, y, z);

		auto& block = m_pChunk->getBlock(position);

		if (block.id = 0)
			continue;

		directions.update(x, y, z);

		// Up/ Down
		if ((m_pChunk->getPosition().y != 0) || y != 0)
		{
			tryAddFaceToMesh(bottomFace, "dirt", position,
				directions.down);
		}
		tryAddFaceToMesh(topFace, "grass_top", position, directions.up);

		// Left/ Right
		tryAddFaceToMesh(leftFace, "grass_side", position, directions.left);
		tryAddFaceToMesh(rightFace, "grass_side", position, directions.right);

		// Front/ Back
		tryAddFaceToMesh(frontFace, "grass_side", position, directions.front);
		tryAddFaceToMesh(backFace, "grass_side", position, directions.back);
	}

}

void ChunkMeshGenerator::tryAddFaceToMesh(const std::array<GLfloat, 12>& blockFace, const std::string& texName, const vn::vec3i& blockPosition, const vn::vec3i& blockFacing)
{
	if (shouldMakeFace(blockFacing))
	{
		faces++;
		//texture stuff
		auto texCoords = resources::TexManager.getTexCoords(texName);
		m_pChunkMesh->addFace(blockFace, texCoords, m_pChunk->getPosition(), blockPosition);
	}
}

bool ChunkMeshGenerator::shouldMakeFace(const vn::vec3i& adjPos)
{
	auto& adjblock = m_pChunk->getBlock(adjPos);
	if (adjblock.id == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}