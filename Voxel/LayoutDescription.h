#pragma once
#include <GL/glew.h>


// Encapsulates the data needed for OpenGL Vertex Attributes.
struct LayoutDescription
{
	enum Type {
		Float = GL_FLOAT
	};

	GLuint index;
	GLuint size;
	Type type;
	GLboolean normalized;
	GLsizei stride;
	void * pointer; // called offset in D3D
};