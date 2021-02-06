#pragma once

#include "../../Engine/Engine.h"

class World
{
public:
	World();
	
	void addObject(vn::GameObject& obj);

	void update(float dt);

	World(const World& world) = delete;

	~World();
private:

};