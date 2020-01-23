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

void GraphicsShader::SetName(std::string name)
{
	Shader::SetName(name);

	auto vShaderName = "VertexShader(" + name + ")";
	auto fShaderName = "FragmentShader(" + name + ")";

	Bind();
	glObjectLabel(GL_SHADER, vertexShader, vShaderName.length(), vShaderName.c_str());
	glObjectLabel(GL_SHADER, fragmentShader, fShaderName.length(), fShaderName.c_str());
	Unbind();
}
