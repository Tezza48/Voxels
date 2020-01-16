#include "GraphicsShader.h"
#include "common.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

GraphicsShader::GraphicsShader(string vsSource, string fsSource) : Shader()
{
	vertexShader = CreateShader(GL_VERTEX_SHADER, vsSource);
	fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsSource);

	Link();
}

GraphicsShader::~GraphicsShader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
