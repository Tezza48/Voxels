#version 460

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 Texcoord;

out vec2 fragCoord;
out vec2 position;

void main()
{
	gl_Position = vec4(Position, 0.0, 1.0);
	fragCoord = Texcoord;
	position = Position;
}