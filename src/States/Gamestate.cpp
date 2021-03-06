#include "Gamestate.h"



GameState::GameState(Application& app)	:	Basestate(app)
{
	app.getCam().follow(m_player);
	m_world.setPlayerCam(&app.getCam());
	vn::Transform t;
	vn::GameObject gobj(t);

	m_gameObjects.push_back(gobj);
}

GameState::~GameState()
{
	m_world.isRunning = false;
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
	m_world.renderWorld(*renderer);
	for (auto& obj : m_gameObjects)
	{
		obj.getCurrentTransform();
		renderer->drawObject(obj);
	}
}

