#pragma once
#include <GL/glew.h>

// Describes an OpenGL object that can be Bound and Unbound.
class RendererResource
{
public:
	// Bind this Resource.
	virtual void Bind() const = 0;
	
	// Unbind this Resource.
	virtual void Unbind() const = 0;
};