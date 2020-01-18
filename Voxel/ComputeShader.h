#pragma once
#include "Shader.h"
#include <string>
#include "Texture2D.h"

enum ImageAccess {
	ReadOnly = GL_READ_ONLY,
	WriteOnly = GL_WRITE_ONLY
};

class ComputeShader :
	public Shader
{
private:
	GLuint shader;

public:
	ComputeShader(std::string source);
	ComputeShader(const ComputeShader &) = delete;
	~ComputeShader();

	void Dispatch(int x, int y, int z) const;

	void BindImageTexture(Texture2D texture, ImageAccess access);

	const GLuint GetProgram() const;
};

