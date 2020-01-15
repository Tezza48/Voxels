#version 460

uniform layout(location = 0) mat4 uViewMatrix;
uniform layout(location = 1) mat4 uProjMatrix;

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec4 in_color;

out vec4 vert_color;

void main()
{
	vec4 pos = vec4(in_position, 0, 1);

	mat4 mvp = uProjMatrix * uViewMatrix;

	gl_Position = mvp * pos;
	vert_color = in_color;
}