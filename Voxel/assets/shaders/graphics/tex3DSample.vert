#version 460

uniform layout(location = 0) mat4 uViewMatrix;
uniform layout(location = 1) mat4 uProjMatrix;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexcoord;

out vec4 vertColor;
out vec2 vertTexcoord;

void main()
{
	gl_Position = vec4(inPosition, 0, 1);

	vertColor = inColor;
	vertTexcoord = inTexcoord;
}