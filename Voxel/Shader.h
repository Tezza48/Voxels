#pragma once
#include <GL/glew.h>
#include <string>
#include "RendererResource.h"
#include <glm/glm.hpp>

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

	void SetUniform1f(const std::string & name, float value) const;
	void SetUniform2f(const std::string & name, glm::vec2 value) const;
	void SetUniform3f(const std::string & name, glm::vec3 value) const;
	void SetUniform4f(const std::string & name, glm::vec4 value) const;

	void SetUniform1i(const std::string & name, int value) const;
	void SetUniform2i(const std::string & name, glm::ivec2 value) const;
	void SetUniform3i(const std::string & name, glm::ivec3 value) const;
	void SetUniform4i(const std::string & name, glm::ivec4 value) const;

	// Inherited via RendererResource
	virtual void SetName(std::string name) override;

protected:
	// Create, Compile and Attach a shader of `type` from the given source code.
	GLuint CreateShader(GLenum type, std::string source);

	// Link this Shader's program once any shaders are attached.
	void Link();
};

