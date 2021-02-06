#include "CubeRenderer.h"

//#include "../../Engine/Registries/ResourceManager.h"

CubeRenderer::CubeRenderer()
{
	
	img.create(16, 16, vn::u8vec4(255.0f, 0.0f, 0.0f, 255.0f));

	//img = resources::TexManager.getSheet();
	//img.saveToFile("test.png");

	m_shader.load("res/Shaders/Other/vert.glsl", "res/Shaders/Other/frag.glsl");

	tex.loadFromImage(img);


	std::vector<float> vertexCoords
	{
		//Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		//Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		//Right
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		//Left
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		//Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		//Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1.
	};

	std::vector<unsigned int> indices
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	std::vector<float> texCoords 
	{ 
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
	};
	
	/*for (auto& f : resources::TexManager.getTexCoords("grass_side"))
	{
		texCoords.push_back(f);
	}
	for (auto& f : resources::TexManager.getTexCoords("grass_side"))
	{
		texCoords.push_back(f);
	}
	for (auto& f : resources::TexManager.getTexCoords("grass_side"))
	{
		texCoords.push_back(f);
	}
	for (auto& f : resources::TexManager.getTexCoords("grass_side"))
	{
		texCoords.push_back(f);
	}
	for (auto& f : resources::TexManager.getTexCoords("grass_top"))
	{
		texCoords.push_back(f);
	}
	for (auto& f : resources::TexManager.getTexCoords("dirt"))
	{
		texCoords.push_back(f);
	}*/



	//m_cubeModel.addData({ vertexCoords, indices, texCoords});
}

void CubeRenderer::addCube(vn::Transform& entity)
{
	m_queue.push_back(entity);
}

void CubeRenderer::render(Camera& cam)
{
	//m_shader.use();
	//m_cubeModel.bindVAO();
	tex.bind();

	//m_shader.setMat4("view", cam.getViewMatrix(cam));
	//m_shader.setMat4("proj", cam.getProjMatrix());

	glEnable(GL_CULL_FACE);

	for (auto& entity : m_queue)
	{
		//m_shader.setMat4("model", makeModelMatrix(entity));

		//glDrawElements(GL_TRIANGLES, m_cubeModel.getNumIndicies(), GL_UNSIGNED_INT, nullptr);
	}
}

void CubeRenderer::clearQueue()
{
	m_queue.clear();
}

CubeRenderer::~CubeRenderer()
{

}
