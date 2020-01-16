#pragma once
#include <GL/glew.h>
#include <string>
#include "RendererResource.h"

// Abstracts OpenGL Program and contains base functionality for working with shaders.
class Shader: 
	RendererResource
{
protected:
	// OpenGL Program object.
	GLuint program;

public:
	// Delete Copy Constructor.
	Shader(const Shader &) = delete;

	virtual ~Shader();

protected:
	Shader();

public:
	// Bind this shader.
	void Bind() const;
	// Unbind this shader. (Binds 0)
	void Unbind() const;

protected:
	// Create, Compile and Attach a shader of `type` from the given source code.
	GLuint CreateShader(GLenum type, std::string source);

	// Link this Shader's program once any shaders are attached.
	void Link();
};

