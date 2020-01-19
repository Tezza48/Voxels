#pragma once
#include <string>

namespace ContentHelper
{
	// Load a shader file and preprocess it for any imports
	std::string LoadShaderSource(const std::string & path);
	std::string ReadFile(const std::string & path);
}