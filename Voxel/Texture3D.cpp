#include "Texture3D.h"

Texture3D::Texture3D(int width, int height, int depth, PixelFormat format): Texture(GL_TEXTURE_3D, format), width(width), height(height), depth(depth)
{
	Bind();

	glTexParameteri(bindTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(bindTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(bindTarget, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(bindTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(bindTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

	Unbind();
}

void Texture3D::SetEmpty()
{
	const auto formats = GetGLFormats();

	glTexImage3D(bindTarget, 0, formats.first, width, height, depth, 0, formats.second, GL_FLOAT, nullptr);
}