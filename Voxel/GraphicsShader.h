#pragma once
#include "Shader.h"
class GraphicsShader :
	public Shader
{
protected:
	GLuint vertexShader;
	GLuint fragmentShader;

public:
	GraphicsShader(std::string vsSource, std::string fsSource);
	virtual ~GraphicsShader();

private:
	GLuint CreateShader(GLenum type, std::string source);
};

