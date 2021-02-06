#pragma once

#include "../Model.h"
#include "../Camera.h"
#include "../Shaders/Shader.h"

class ComputeRenderer
{
public:
	ComputeRenderer();

	//void addCube(Entity& entity);
	void render();

	~ComputeRenderer();
private:
	Shader m_shader;
	Model m_computeModel;
};