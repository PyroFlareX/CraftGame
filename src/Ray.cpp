#include "Ray.h"

Ray::Ray(vn::vec3 pos, vn::vec3 direction)
{
	position = pos;
	angle = direction;
}

void Ray::step(float increment)
{
	
}

vn::vec3 Ray::getEnd()
{
	
	return vn::vec3();
}
