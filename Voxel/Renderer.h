#pragma once
#include <GL/glew.h>
#include "Window.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "Mesh.h"

class Renderer
{
private: 
	Window window;

public:
	Renderer(Window & window);
	~Renderer();

	void Clear();
	void SetClearColor(glm::vec4 color);
	void SwapBuffers();

	void DrawMesh(const Mesh & mesh, glm::mat4 view, glm::mat4 projection);

private:
#if DEBUG || _DEBUG
	static void OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam);
#endif

	static void OnSizeCallback(void * context, int width, int height);

	void OnSize(int width, int height);
};

