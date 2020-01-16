#version 460

in vec4 vertColor;
in vec2 vertTexcoord;

out vec4 fragColor;

void main()
{
	fragColor = vec4(vertTexcoord, 0, 1);
}