#include "Renderer.h"

Renderer::Renderer()
{
	m_shader.load("res/Shaders/quad.vs", "res/Shaders/quad.fs");

	//For Screen Quad
	vn::Mesh mesh;
	vn::Vertex vert;

	vert.position = vn::vec3(-1.0f, 1.0f, 0.0f);
	vert.uv = vn::vec2(0.0f, 1.0f);
	mesh.vertices.push_back(vert);
	vert.position = vn::vec3(-1.0f, -1.0f, 0.0f);
	vert.uv = vn::vec2(0.0f, 0.0f);
	mesh.vertices.push_back(vert);
	vert.position = vn::vec3(1.0f, -1.0f, 0.0f);
	vert.uv = vn::vec2(1.0f, 0.0f);
	mesh.vertices.push_back(vert);
	vert.position = vn::vec3(-1.0f, 1.0f, 0.0f);
	vert.uv = vn::vec2(0.0f, 1.0f);
	mesh.vertices.push_back(vert);
	vert.position = vn::vec3(1.0f, -1.0f, 0.0f);
	vert.uv = vn::vec2(1.0f, 0.0f);
	mesh.vertices.push_back(vert);
	vert.position = vn::vec3(1.0f, 1.0f, 0.0f);
	vert.uv = vn::vec2(1.0f, 1.0f);
	mesh.vertices.push_back(vert);

	m_quad.addData(mesh);
}

void Renderer::drawCube(vn::Transform& entity)
{
	m_cubeRenderer.addCube(entity);
}

void Renderer::drawObject(vn::GameObject& entity)
{
	m_generalRenderer.addInstance(entity);
}

void Renderer::doCompute()
{

}


void Renderer::render(Camera& cam)
{
	//Main Pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	m_cubeRenderer.render(cam);
	m_generalRenderer.render(cam);
	m_computeRenderer.render();
}

void Renderer::finish()
{
	//Second Pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader.use();
	m_quad.bindVAO();
	glDisable(GL_DEPTH_TEST);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	clearQueue();
}

void Renderer::clearQueue()
{
	m_cubeRenderer.clearQueue();
	m_generalRenderer.clearQueue();
}

Renderer::~Renderer()
{
    //dtor
}
