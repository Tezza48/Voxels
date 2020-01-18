#include "Renderer.h"
#include "common.h"
#include <string>
#include <iostream>
#include <glm/ext.hpp>

using namespace glm;

using std::cout;
using std::endl;
using std::string;

Renderer::Renderer(Window & window) : window(window)
{
	glewInit();

	// TODO: Set up window resize callback
	window.SetWindowResizeCallback(this, OnSizeCallback);

#if DEBUG || _DEBUG
	glDebugMessageCallback(OpenGLErrorCallback, nullptr);
#endif
}

Renderer::~Renderer()
{
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::SetClearColor(glm::vec4 color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::SwapBuffers()
{
	window.SwapBuffers();
}

void Renderer::SetTextureSampler(int samplerSlot, Texture * texture)
{
	GLenum slot = GL_TEXTURE0 + samplerSlot;

	if (slot < GL_TEXTURE0 || slot > GL_TEXTURE31)
	{
		cout << "Sampler Slot \"" << samplerSlot << "\" is out of range 0 to 31. No sampler was bound" << endl;
		return;
	}

	glActiveTexture(slot);
	texture->Bind();
}

void Renderer::DrawMesh(const Mesh & mesh, mat4 view, mat4 projection)
{
	mesh.Bind();

	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(projection));

	const int numBuffers = mesh.GetNumIndexBuffers();

	if (numBuffers < 1)
	{
		glDrawArrays(GL_TRIANGLES, 0, mesh.GetNumVertices());
	}
	else
	{
		for (int i = 0, l = numBuffers; i < l; i++)
		{
			const auto buffer = mesh.GetIndexBuffer(i);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.first);
			glDrawElements(GL_TRIANGLES, buffer.second, GL_UNSIGNED_INT, nullptr);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	mesh.Unbind();
}

#if DEBUG || _DEBUG
void Renderer::OpenGLErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
{
	string sourceStr;
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		sourceStr = "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceStr = "Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceStr = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceStr = "Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		sourceStr = "Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		sourceStr = "Other";
		break;
	}

	string typeStr;
	switch (type)
	{
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeStr = "Depricated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeStr = "Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		typeStr = "Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		typeStr = "Performance";
		break;
	case GL_DEBUG_TYPE_OTHER:
		typeStr = "Other";
		break;
	case GL_DEBUG_TYPE_MARKER:
		typeStr = "Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		typeStr = "Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		typeStr = "Pop Group";
		break;
	default:
		typeStr = "Unknown Type";
		break;
	}

	string severityStr;
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		severityStr = "High Severity";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severityStr = "Medium Severity";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		severityStr = "Low Severity";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		severityStr = "Notification";
		return;
		break;
	}

	cout << "ERROR-" << typeStr << ". ";

	cout << severityStr << " : " << sourceStr;
	
	cout << " ID: 0x" << std::hex << id << " 0x" << type << std::dec << " ";

	cout << "Message(" << message << ")" << endl;
}
#endif

void Renderer::OnSizeCallback(void * context, int width, int height)
{
	reinterpret_cast<Renderer *>(context)->OnSize(width, height);
}

void Renderer::OnSize(int width, int height)
{
	cout << "Resize" << endl;
}
