#pragma once
#include <GL/glew.h>
#include "Window.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "GraphicsShader.h"

// Class for abstracting OpenGL Rendering calls.
class Renderer
{
private: 
	// Window object this renderer draws to.
	Window window;

	Mesh * spriteQuad;
	GraphicsShader * spriteShader;

public:
	// Creates an instance of `Renderer` and sets the window.
	Renderer(Window & window);
	~Renderer();

	// Clear the currently bound render target.
	void Clear();

	// Set the color that `Clear` will clear to.
	void SetClearColor(glm::vec4 color);

	// Swap the Window's render targets.
	void SwapBuffers();

	// Bind a Texture to a texture slot.
	void SetTextureSampler(int samplerSlot, const Texture * texture);

	// Draw a mesh.
	void DrawMesh(const Mesh & mesh, glm::mat4 view, glm::mat4 projection);

	// Draw a texture to the screen.
	void DrawTexture(const Texture * texture, glm::vec4 rect);

private:
#if DEBUG || _DEBUG
	// 
	static void OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam);
#endif

	// Calls `OnSize` on the provided context.
	static void OnSizeCallback(void * context, int width, int height);

	// Callback for when the window is resized.
	void OnSize(int width, int height);
};

