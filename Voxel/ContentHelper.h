#pragma once
#include <string>
#include "Texture.h"

namespace ContentHelper
{
	// Load a shader file and preprocess it for any imports.
	std::string LoadShaderSource(const std::string & path);

	// Read a text file.
	std::string ReadFile(const std::string & path);

	// Load a texture. Must call CleanupTextureFile after data is uesd.
	unsigned char * LoadTextureFile(const std::string & path, int * width, int * height, PixelFormat * format);

	// Free up the texture data.
	void CleanupTextureFile(unsigned char * textureData);
}