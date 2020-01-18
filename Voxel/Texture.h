#pragma once
#include <GL/glew.h>
#include "RendererResource.h"
#include <utility>

enum PixelFormat {
	R, RG, RGB, RGBA
};

class Texture : 
	RendererResource
{
protected:
	GLuint texture;
	GLenum bindTarget;
	PixelFormat pixelFormat;

public:
	Texture(GLenum bindTarget, PixelFormat format);
	Texture(const Texture &) = delete;
	virtual ~Texture();

	// Inherited via RendererResource
	virtual void Bind() const override;
	virtual void Unbind() const override;

	std::pair<unsigned int, unsigned int> GetGLFormats() const;

	GLuint GetInternalTexture() const;
	PixelFormat GetPixelFormat() const;
};

