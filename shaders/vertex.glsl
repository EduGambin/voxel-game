#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_coord;
layout (location = 2) in vec3 a_normal;

uniform mat4 mvp;

out vec2 TexCoord;
out vec3 NormalVector;

void main()
{
	gl_Position = mvp * vec4(a_pos, 1.0);
	TexCoord = a_tex_coord;
	NormalVector = a_normal;
}