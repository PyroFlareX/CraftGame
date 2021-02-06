#include "GeneralRenderer.h"

//#include "../../Engine/Registries/ResourceManager.h"

GeneralRenderer::GeneralRenderer()
{
	img.loadFromFile("res/container.jpg");

	m_shader.load("res/Shaders/model.vs", "res/Shaders/model.fs");
	m_lampshader.load("res/Shaders/lamp.vs", "res/Shaders/lamp.fs");
	
	tex.loadFromImage(img);

	m_generalModel.emplace_back(std::make_unique<Model>(vn::loadMeshFromObj("res/Models/sphere.obj")));
	m_generalModel.emplace_back(std::make_unique<Model>(vn::loadMeshFromObj("res/Models/cube.obj")));
	m_generalModel.emplace_back(std::make_unique<Model>(vn::loadMeshFromObj("res/Models/Monkey.obj")));
	m_generalModel.emplace_back(std::make_unique<Model>(vn::loadMeshFromObj("res/Models/Torus.obj")));
	
	m_textures.emplace_back(std::make_unique<vn::Texture>("res/container.jpg"));
	m_textures.emplace_back(std::make_unique<vn::Texture>("res/container1.jpg"));

	//m_generalModel.addData(vn::loadMeshFromObj("res/Models/Sword.obj"));
	//m_generalModel.addData(vn::loadMeshFromObj("res/Models/mythra.obj"));
	//m_generalModel.addData(vn::loadMeshFromObj("res/Models/teapot.obj"));
	//m_generalModel.addData(vn::loadMeshFromObj("res/Models/chalet.obj"));

	m_lampModel.addData(vn::loadMeshFromObj("res/Models/cube.obj"));
}

void GeneralRenderer::addInstance(vn::GameObject& entity)
{
	m_queue.push_back(entity);
}

void GeneralRenderer::render(Camera& cam)
{
	vn::vec3 lightpos(5.0f, 0.0f, -1.0f);

	m_shader.use();
	
	//tex.bind();

	m_shader.setMat4("view", cam.getViewMatrix());
	m_shader.setMat4("proj", cam.getProjMatrix());
	m_shader.setVec3("lightsrc", lightpos);

	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int lastmodel = -1;
	int lasttexture = -1;
	for (auto& entity : m_queue)
	{
		vn::Transform t = entity.getCurrentTransform();

		if (entity.model_id != lastmodel)
		{
			m_generalModel[entity.model_id].get()->bindVAO();
			lastmodel = entity.model_id;
		}
		if (entity.texture_id != lasttexture)
		{
			m_textures[entity.texture_id].get()->bind();
			lasttexture = entity.texture_id;
		}
		
		
		m_shader.setMat4("model", vn::makeModelMatrix(t));
		m_shader.setMat4("normmat", vn::makeNormalMatrix(t));
		
		glDrawElements(GL_TRIANGLES, m_generalModel[entity.model_id].get()->getNumIndicies(), GL_UNSIGNED_INT, nullptr);
	}
	
	

	vn::Transform trans;
	trans.rescale(trans, vn::vec3(0.5f, 0.5f, 0.5f));
	trans.translate(trans, lightpos);
	m_lampshader.use();
	m_lampModel.bindVAO();
	m_lampshader.setMat4("view", cam.getViewMatrix());
	m_lampshader.setMat4("proj", cam.getProjMatrix());
	m_lampshader.setMat4("model", makeModelMatrix(trans));
	glDrawElements(GL_TRIANGLES, m_lampModel.getNumIndicies(), GL_UNSIGNED_INT, nullptr);
}

void GeneralRenderer::clearQueue()
{
	m_queue.clear();
}

GeneralRenderer::~GeneralRenderer()
{

}
