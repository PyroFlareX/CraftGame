#include "Context.h"

Context::Context()
{
	m_window.create(sf::VideoMode(1280, 720), "CraftGame");

	initAPI();
}

void Context::clear()
{
	m_window.clear();
}

void Context::update()
{
	m_window.display();
}

void Context::close()
{
	m_window.close();
}

void Context::initAPI()
{
	if (!gladLoadGL())
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
	}
	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

bool Context::isOpen()
{
	return m_window.isOpen();
}

sf::RenderWindow* Context::getContext()
{
	return &m_window;
}

Context::~Context()
{
	
}
