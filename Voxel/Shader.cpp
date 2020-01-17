#include "Shader.h"
#include "common.h"
#include <iostream>
#include <glm/ext.hpp>

using std::cout;
using std::endl;
using std::string;
using namespace glm;

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

	glValidateProgram(program);
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

void Shader::SetUniform1f(const string & name, float value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetUniform2f(const string & name, vec2 value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void Shader::SetUniform3f(const string & name, vec3 value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetUniform4f(const string & name, vec4 value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1i(const string & name, int value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetUniform2i(const string & name, ivec2 value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform2i(location, value.x, value.y);
}

void Shader::SetUniform3i(const string & name, ivec3 value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform3i(location, value.x, value.y, value.z);
}

void Shader::SetUniform4i(const string & name, ivec4 value) const
{
	const auto location = glGetUniformLocation(program, name.c_str());
	glUniform4i(location, value.x, value.y, value.z, value.w);
}

