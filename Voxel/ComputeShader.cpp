#include "ComputeShader.h"

using std::string;

//ComputeShader::ComputeShader(string source)
//{
//	shader = CreateShader(GL_COMPUTE_SHADER, source);
//
//	Link();
//}
//
//
//ComputeShader::~ComputeShader()
//{
//}

ComputeShader::ComputeShader(std::string source)
{
	shader = CreateShader(GL_COMPUTE_SHADER, source);
	
	Link();
}

ComputeShader::~ComputeShader()
{
	glDeleteShader(shader);
}

void ComputeShader::Dispatch(int x, int y, int z) const
{
	glDispatchCompute(x, y, z);
}

const GLuint ComputeShader::GetProgram() const
{
	return program;
}
