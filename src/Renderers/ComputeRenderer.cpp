#include "ComputeRenderer.h"

ComputeRenderer::ComputeRenderer()
{
	m_shader.addShader("res/Shaders/Other/compute.glsl", GL_COMPUTE_SHADER);
}

void ComputeRenderer::render()
{
	m_shader.use();
	
	glDispatchCompute(1, 1, 1);
}

ComputeRenderer::~ComputeRenderer()
{

}
