#version 460

layout(location = 0) in vec2 Position;

out vec2 fragCoord;

void main()
{
	gl_Position = vec4(Position, 0.0, 1.0);
	fragCoord = Position;
}