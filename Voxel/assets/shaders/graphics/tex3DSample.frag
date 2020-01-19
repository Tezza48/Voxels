#version 460

layout(binding = 0) uniform sampler3D uNoiseTexture;
uniform float uTime;

in vec4 vertColor;
in vec2 vertTexcoord;

out vec4 fragColor;

void main()
{
	float texSample = texture(uNoiseTexture, vec3(vertTexcoord, uTime / 16)).x;

	fragColor = vec4(texSample.xxx, 1);
}