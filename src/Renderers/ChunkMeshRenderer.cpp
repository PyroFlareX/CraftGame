#include "ChunkMeshRenderer.h"

#include "../World/ChunkMesh.h"
#include "../../Engine/Registries/ResourceManager.h"


ChunkMeshRenderer::ChunkMeshRenderer()
{
	resources::TexManager.getSheet().saveToFile("res/Textures/BlockSheet.png");

	m_tex.loadFromFile("res/Textures/BlockSheet.png");

	m_shader.load("res/Shaders/ChunkVert.glsl", "res/Shaders/ChunkFrag.glsl");
}

void ChunkMeshRenderer::addInstance(ChunkMesh& entity)
{
	m_queue.emplace_back(&entity.getModel().getInfo());
}

void ChunkMeshRenderer::render(Camera& cam)
{
	m_shader.use();

	m_tex.bind();

	m_shader.setMat4("view", cam.getViewMatrix());
	m_shader.setMat4("proj", cam.getProjMatrix());
	int i = 0;

	
	for (auto& chunk : m_queue)
	{
		glBindVertexArray(chunk->VAO);

		glDrawElements(GL_TRIANGLES, chunk->indiciesCount, GL_UNSIGNED_INT, nullptr);
	}

	m_queue.clear();
}

void ChunkMeshRenderer::clearQueue()
{
	m_queue.clear();
}
