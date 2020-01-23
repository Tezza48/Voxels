#version 460

uniform ivec2 uResolution;
uniform vec4 uRect;

in vec2 vertPosition;
in vec2 vertTexcoord;

out vec2 fragTexcoord;

void main()
{
	vec2 pos = (vertPosition * 2) / uResolution;

	pos *= uRect.zw;
	pos += uRect.xy;
	pos = pos + vec2(-1, 1);

//	pos *= uRect.zw;

	gl_Position = vec4(pos, 0, 1);
	fragTexcoord = vertTexcoord;
}