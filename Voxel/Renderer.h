#pragma once
#include <GL/glew.h>
#include "Window.h"
#include <glm/vec4.hpp>
#include "Mesh.h"

class Renderer
{
private: 
	Window window;

public:
	Renderer(const Window & window);
	~Renderer();

	void Clear();
	void SetClearColor(glm::vec4 color);
	void SwapBuffers();

	void DrawMesh(const Mesh & mesh);

private:
#if DEBUG || _DEBUG
	static void OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam);
#endif
};

