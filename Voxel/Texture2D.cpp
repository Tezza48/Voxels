#include "Texture2D.h"

Texture2D::Texture2D(int width, int height, PixelFormat format): width(width), height(height), pixelFormat(format)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);

	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	Unbind();
}


Texture2D::~Texture2D()
{
}

void Texture2D::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::SetEmpty()
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

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, nullptr);
}

GLuint Texture2D::GetInternalTexture() const
{
	return texture;
}

PixelFormat Texture2D::GetPixelFormat() const
{
	return pixelFormat;
}

GLenum Texture2D::PixelFormatToGLInternalFormat(PixelFormat format)
{
	switch (format)
	{
	case PixelFormat::R:
		return GL_R8;
		break;
	case PixelFormat::RG:
		return GL_RG8;
		break;
	case PixelFormat::RGB:
		return GL_RGB8;
		break;
	case PixelFormat::RGBA:
		return GL_RGBA8;
		break;
	default:
		break;
	}
}
