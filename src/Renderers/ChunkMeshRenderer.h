#pragma once

#include "../Model.h"
#include "../Camera.h"
#include "../Shaders/Shader.h"
#include "../../Engine/Engine.h"

class ChunkMesh;

class ChunkMeshRenderer
{
public:
	ChunkMeshRenderer();

	void addInstance(ChunkMesh& entity);
	void render(Camera& cam);

	void clearQueue();
private:
	std::vector<vn::renderInfo*> m_queue;

	Shader m_shader;
	sf::Texture m_texture;
};