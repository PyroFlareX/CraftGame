#include "Gamestate.h"



GameState::GameState(Application& app)	:	Basestate(app)
{
	app.getCam().follow(m_player);
	vn::Transform t;
	vn::GameObject gobj(t);

	m_gameObjects.push_back(gobj);
}

GameState::~GameState()
{

}

bool GameState::input()
{

	vInput = Input::getInput();

	m_player.getInput(vInput, false);


	return false;
}

void GameState::update(float dt)
{
	m_player.update(dt);
	m_world.update(dt);

	for (auto& obj : m_gameObjects)
	{
		obj.update();
	}
}

void GameState::lateUpdate(Camera* cam)
{
	
}

void GameState::render(Renderer* renderer)
{		
	for (auto& obj : m_gameObjects)
	{
		obj.getCurrentTransform();
		renderer->drawObject(obj);
	}
}

