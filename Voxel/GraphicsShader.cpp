#include "GraphicsShader.h"
#include "common.h"
#include <iostream>

using std::cout;
using std::endl;

GraphicsShader::GraphicsShader(std::string vsSource, std::string fsSource)
{
	vertexShader = CreateShader(GL_VERTEX_SHADER, vsSource);
	fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE)
	{
		int logLength;
		GLchar log[1024];
		glGetProgramInfoLog(program, 1024, &logLength, log);
		std::cout << "Program Link Error: " << log << std::endl;
	}
}

GraphicsShader::~GraphicsShader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLuint GraphicsShader::CreateShader(GLenum type, std::string source)
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

	return shader;
}
