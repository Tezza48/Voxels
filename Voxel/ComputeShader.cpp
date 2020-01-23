#include "ComputeShader.h"

using std::string;

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

void ComputeShader::BindImageTexture(Texture * texture, ImageAccess access, int unit)
{
	glBindImageTexture(unit, texture->GetInternalTexture(), 0, GL_FALSE,
		0, access, texture->GetGLFormats().first);
}

const GLuint ComputeShader::GetProgram() const
{
	return program;
}

void ComputeShader::SetName(std::string name)
{
	Shader::SetName(name);

	auto shaderName = "ComputeShader(" + name + ")";

	Bind();
	glObjectLabel(GL_SHADER, shader, shaderName.length(), shaderName.c_str());
	Unbind();
}
