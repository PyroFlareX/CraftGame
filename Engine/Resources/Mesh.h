#pragma once

#include <vector>
#include "../Types/Types.h"


namespace vn
{
	struct Vertex
	{
		vn::vec3 position;
		vn::vec3 normal;
		vn::vec2 uv;
	};

	struct Mesh
	{
		std::vector<vn::Vertex> vertices;
		std::vector<unsigned int> indicies;
	};

	struct renderInfo
	{
		unsigned int VAO = 0;
		int indiciesCount = 0;
		inline void reset()
		{
			VAO = 0;
			indiciesCount = 0;
		}
	};
}