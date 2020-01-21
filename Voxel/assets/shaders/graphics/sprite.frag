#version 460

uniform sampler2D uSpriteTexture;

in vec2 fragTexcoord;

out vec4 fragColor;

void main()
{
	fragColor = texture(uSpriteTexture, fragTexcoord);
}