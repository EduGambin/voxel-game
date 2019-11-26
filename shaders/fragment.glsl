#version 330 core

in vec2 TexCoord;
in vec3 NormalVector;

out vec4 FragColor;

uniform sampler2D texture_atlas;

const vec3 light_direction = -vec3(1.0, -1.0, 0.0);

float get_light_value(vec3 nv)
{
	float x = dot(normalize(light_direction), nv);
	return (x + 1.5)*0.4;
}

void main()
{
	float light = get_light_value(NormalVector);
	FragColor = texture(texture_atlas, TexCoord) * vec4(light, light, light, 1.0);
}