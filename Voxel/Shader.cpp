#include "Shader.h"
#include "common.h"

Shader::Shader()
{
	program = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::Bind() const
{
	glUseProgram(program);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

