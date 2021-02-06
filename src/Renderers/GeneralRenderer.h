#pragma once

#include "../Model.h"
#include "../Camera.h"
#include "../Shaders/Shader.h"
#include "../../Engine/Engine.h"

class GeneralRenderer
{
public:
	GeneralRenderer();

	void addInstance(vn::GameObject& entity);
	void render(Camera& cam);

	void clearQueue();
	
	~GeneralRenderer();
private:
	std::vector<vn::GameObject> m_queue;
	
	Shader m_shader;
	Shader m_lampshader;

	std::vector<std::unique_ptr<Model>> m_generalModel;
	std::vector<std::unique_ptr<vn::Texture>> m_textures;
	
	Model m_lampModel;
	vn::Image img;
	vn::Texture tex;
};

