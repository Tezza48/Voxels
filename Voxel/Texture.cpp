#include "Texture.h"

using std::pair;

Texture::Texture(GLenum bindTarget, PixelFormat format) : bindTarget(bindTarget), pixelFormat(format)
{
	glCreateTextures(bindTarget, 1, &texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::Bind() const
{
	glBindTexture(bindTarget, texture);
}

void Texture::Unbind() const
{
	glBindTexture(bindTarget, 0);
}

std::pair<unsigned int, unsigned int> Texture::GetGLFormats() const
{
	GLenum internalFormat;
	GLenum format;

	switch (pixelFormat)
	{
	case PixelFormat::R:
		internalFormat = GL_R8;
		format = GL_RED;
		break;
	case PixelFormat::RG:
		internalFormat = GL_RG8;
		format = GL_RG;
		break;
	case PixelFormat::RGB:
		internalFormat = GL_RGB8;
		format = GL_RGB;
		break;
	case PixelFormat::RGBA:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		break;
	default:
		break;
	}

	return pair<unsigned int, unsigned int>(internalFormat, format);
}

GLuint Texture::GetInternalTexture() const
{
	return texture;
}

PixelFormat Texture::GetPixelFormat() const
{
	return pixelFormat;
}
