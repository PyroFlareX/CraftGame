#ifndef RENDERER_H
#define RENDERER_H

#include "../Camera.h"
#include "CubeRenderer.h"
#include "GeneralRenderer.h"
#include "ComputeRenderer.h"
#include "../../Engine/Engine.h"


class Renderer
{
    public:
        Renderer();

		void drawCube(vn::Transform& entity);
		void drawObject(vn::GameObject& entity);
		void doCompute();
		void render(Camera& cam);
		void finish();

		void clearQueue();

        ~Renderer();
    protected:

    private:
		CubeRenderer m_cubeRenderer;
		GeneralRenderer m_generalRenderer;
		ComputeRenderer m_computeRenderer;

		Model m_quad;
		Shader m_shader;
};

#endif // RENDERER_H
