#pragma once
#include "Shader.h"

// Abstracts Opengl Program for the rendering pipeline.
class GraphicsShader :
	public Shader
{
protected:
	// OpenGL vertex shader object.
	GLuint vertexShader;
	// OpenGL fragment shader object.
	GLuint fragmentShader;

public:
	// Create shader from the given sourcecode.
	GraphicsShader(std::string vsSource, std::string fsSource);
	virtual ~GraphicsShader();
};

