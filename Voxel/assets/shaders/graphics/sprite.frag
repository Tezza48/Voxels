#version 460

uniform sampler2D uSpriteTexture;

in vec2 fragTexcoord;

out vec4 fragColor;

void main()
{
	vec4 col = texture(uSpriteTexture, fragTexcoord);

	if (col.a < 0.01) discard;

	fragColor = col;
}