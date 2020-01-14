#pragma once
#include <GL/glew.h>
#include <string>
#include "IBindableResource.h"

class Shader: 
	IBindableResource
{
protected:
	GLuint program;

public:
	Shader();
	virtual ~Shader();

	void Bind() const;
	void Unbind() const;
};

