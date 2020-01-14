#pragma once
#include <GL/glew.h>

struct LayoutDescription
{
	GLuint index;
	GLuint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	void * pointer; // called offset in D3D
};