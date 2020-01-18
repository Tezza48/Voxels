#include "Texture2D.h"

Texture2D::Texture2D(int width, int height, PixelFormat format): Texture(GL_TEXTURE_2D, format), width(width), height(height)
{
	Bind();

	glTexParameteri(bindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(bindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(bindTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(bindTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

	Unbind();
}

void Texture2D::SetEmpty()
{
	const auto formats = GetGLFormats();

	glTexImage2D(bindTarget, 0, formats.first, width, height, 0, formats.second, GL_FLOAT, nullptr);
}