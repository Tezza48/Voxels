#pragma once
#include "RendererResource.h"
#include <vector>
#include <type_traits>

enum PixelFormat {
	R, RG, RGB, RGBA
};

class Texture2D :
	public RendererResource
{
public:

private:
	GLuint texture;

	int width;
	int height;
	PixelFormat pixelFormat;

public:
	Texture2D(int width, int height, PixelFormat format);
	~Texture2D();

	// Inherited via RendererResource
	virtual void Bind() const;
	virtual void Unbind() const;

	void SetEmpty();

	GLuint GetInternalTexture() const;
	PixelFormat GetPixelFormat() const;

	static GLenum PixelFormatToGLInternalFormat(PixelFormat format);
};