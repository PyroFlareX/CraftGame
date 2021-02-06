#pragma once

#include "../Model.h"
#include "../Camera.h"
#include "../Shaders/Shader.h"
#include "../../Engine/Engine.h"

class CubeRenderer
{
public:
	CubeRenderer();

	void addCube(vn::Transform& entity);
	void render(Camera& cam);

	void clearQueue();

	~CubeRenderer();
private:
	std::vector<vn::Transform> m_queue;
	Shader m_shader;
	Model m_cubeModel;
	vn::Image img;
	vn::Texture tex;
};

