#include "UtilFunctions.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace vn
{
	inline float lerp(float pos1, float pos2, float gradient) noexcept
	{
		return (((pos2 - pos1) * gradient) + pos1);
	}

	inline vec2 lerp(vec2 pos1, vec2 pos2, float gradient) noexcept
	{
		return vec2(((pos2 - pos1) * gradient) + pos1);
	}

	inline vec3 lerp(vec3 pos1, vec3 pos2, float gradient) noexcept
	{
		return vec3(((pos2 - pos1) * gradient) + pos1);
	}

	inline vec4 lerp(vec4 pos1, vec4 pos2, float gradient) noexcept
	{
		return vec4(((pos2 - pos1) * gradient) + pos1);
	}

	mat4 makeProjectionMatrix(const float fov, const vec2 contextSize) noexcept
	{
		mat4 proj = glm::perspective(glm::radians(fov), contextSize.x / contextSize.y, 0.001f, 1000.0f);
		return proj;
	}

	mat4 makeViewMatrix(const Transform& camera) noexcept
	{
		mat4 matrix = mat4(1.0f);

		matrix = glm::rotate(matrix, glm::radians(camera.rot.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.rot.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(camera.rot.z), { 0, 0, 1 });

		matrix = glm::translate(matrix, -camera.pos);

		return matrix;
	}

	//Rotations in Degrees, NOT RADIANS
	mat4 makeModelMatrix(const Transform& entity) noexcept
	{
		mat4 matrix = mat4(1.0f);

		matrix = glm::translate(matrix, entity.pos);

		matrix = glm::rotate(matrix, glm::radians(entity.rot.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(entity.rot.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(entity.rot.z), { 0, 0, 1 });

		matrix = glm::scale(matrix, entity.scale);

		return matrix;
	}
	mat3 makeNormalMatrix(const Transform& entity) noexcept
	{
		return mat3(glm::transpose(glm::inverse(makeModelMatrix(entity))));
	}
	Transform getTransformFromModelMatrix(mat4& matrix) noexcept
	{
		Transform trans;
		glm::vec3 scale;
		glm::quat rot;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(matrix, scale, rot, translation, skew, perspective);
		rot = glm::conjugate(rot);
		
		trans.pos = translation;
		trans.scale = scale;
		trans.rot = glm::eulerAngles(rot);
		trans.rot = vec3(glm::degrees(trans.rot.x), glm::degrees(trans.rot.y), glm::degrees(trans.rot.z));

		return trans;
	}
}