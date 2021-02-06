#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 textureCoordinates;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normmat;
uniform vec3 lightsrc;

void main()
{
	fragPos = vec3(model * vec4(aPos, 1.0));
	textureCoordinates = aTexCoord;
	normal = vec3(model * vec4(aNormal, 0.0));
	gl_Position = proj * view * model * vec4(aPos, 1.0);
}