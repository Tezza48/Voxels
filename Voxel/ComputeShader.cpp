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

void ComputeShader::BindImageTexture(Texture2D texture, ImageAccess access)
{
	glBindImageTexture(0, texture.GetInternalTexture(), 0, GL_FALSE,
		0, access, Texture2D::PixelFormatToGLInternalFormat(texture.GetPixelFormat()));
}

const GLuint ComputeShader::GetProgram() const
{
	return program;
}
