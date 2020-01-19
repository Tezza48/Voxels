#version 460

layout(binding = 0) uniform sampler2D uNoiseTexture;

in vec4 vertColor;
in vec2 vertTexcoord;

out vec4 fragColor;

void main()
{
	fragColor = vec4(texture(uNoiseTexture, vertTexcoord).xxx, 1);
}