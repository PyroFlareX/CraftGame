#pragma once

#include "../Engine/Engine.h"

class Ray
{
public:
	Ray(vn::vec3 pos, vn::vec3 direction);

	void step(float increment);
	vn::vec3 getEnd();

private:
	vn::vec3 position;
	vn::vec3 angle;
};