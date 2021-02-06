#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cctype>
#include <functional>


namespace vn
{
	typedef glm::vec2	vec2;
	typedef glm::vec3	vec3;
	typedef glm::vec4	vec4;

	typedef glm::u8vec2	u8vec2;
	typedef glm::u8vec3	u8vec3;
	typedef glm::u8vec4	u8vec4;
	
	typedef glm::ivec2	vec2i;
	typedef glm::ivec3	vec3i;
	typedef glm::ivec4	vec4i;
	
	typedef glm::mat4	mat4;
	typedef glm::mat3	mat3;

	class Transform
	{
	public:
		vec3 pos = vec3(0.0f, 0.0f, 0.0f);
		vec3 rot = vec3(0.0f, 0.0f, 0.0f);
		vec3 scale = vec3(1.0f, 1.0f, 1.0f);
		
		vec3 angularMomentum = vec3(0.0f);
		vec3 velocity = vec3(0.0f);

		bool interactable = true;

		static Transform translate(Transform& entity, const vec3& offset)
		{
			entity.pos += offset;
			return entity;
		}

		static Transform rotate(Transform& entity, const vec3& angle)
		{
			entity.rot += angle;
			return entity;
		}

		static Transform rescale(Transform& entity, const vec3& relativeScale)
		{
			entity.scale = entity.scale * relativeScale;
			return entity;
		}
	};
}

//For hashing (e.g. usage in std::maps)
namespace std
{
	template<>
	struct hash<vn::vec3>
	{
		size_t operator()(const vn::vec3& vect) const noexcept
		{
			std::hash<decltype(vect.x)> hasher;

			auto hash1 = hasher(vect.x);
			auto hash2 = hasher(vect.y);
			auto hash3 = hasher(vect.z);

			return std::hash<decltype(vect.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
		}
	};
}