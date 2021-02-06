#version 330 core
out vec4 FragColor;

in vec2 textureCoordinates;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D ourTexture;
uniform vec3 lightsrc;

void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightsrc - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec4 result = vec4(ambient + diffuse, 1.0);
	
	FragColor = texture(ourTexture, textureCoordinates) * result;
	//FragColor = vec4(1.0, 0.1, 0.1, 1.0) * result;
} 