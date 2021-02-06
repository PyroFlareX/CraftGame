#pragma once

#include "../Types/Types.h"

namespace vn
{
	inline float	lerp(float pos1, float pos2, float gradient) noexcept;
	inline vec2	lerp(vec2 pos1, vec2 pos2, float gradient) noexcept;
	inline vec3	lerp(vec3 pos1, vec3 pos2, float gradient) noexcept;
	inline vec4	lerp(vec4 pos1, vec4 pos2, float gradient) noexcept;

	mat4 makeProjectionMatrix(const float fov, const vec2 contextSize) noexcept;
	mat4 makeViewMatrix(const Transform& camera) noexcept;
	mat4 makeModelMatrix(const Transform& entity) noexcept;
	mat3 makeNormalMatrix(const Transform& entity) noexcept;

	Transform getTransformFromModelMatrix(mat4& matrix) noexcept;
}