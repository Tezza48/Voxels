#include "Shader.h"
#include "common.h"
#include <iostream>

using std::cout;
using std::endl;

Shader::Shader()
{
	program = glCreateProgram();
}

GLuint Shader::CreateShader(GLenum type, std::string source)
{
	const GLuint shader = glCreateShader(type);

	const char * cstrSource = source.c_str();
	const GLint lenSource = (GLint)source.length();

	glShaderSource(shader, 1, &cstrSource, &lenSource);

	glCompileShader(shader);

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		int logLength;
		GLchar log[1024];
		glGetShaderInfoLog(shader, 1024, &logLength, log);
		cout << "Shader Compile Error: " << log << endl;
	}

	glAttachShader(program, shader);

	return shader;
}

void Shader::Link()
{
	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		int logLength;
		GLchar log[1024];
		glGetProgramInfoLog(program, 1024, &logLength, log);
		cout << "Program Link Error: " << log << endl;
	}
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

