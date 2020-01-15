#include "Window.h"

#include <iostream>

using std::cout;
using std::endl;
using std::string;

void * Window::sizeCallbackContext;
WindowSizeFN Window::sizeCallback;

Window::Window(int width, int height, string title) : window(nullptr), width(width), height(height)
{
	if (!glfwInit())
	{
		cout << __FILE__ << ":" << __LINE__ << "Failed to Init GLFW";
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

#if DEBUG || _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#else
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#endif

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		cout << __FILE__ << ":" << __LINE__ << "Failed to Init GLFW";
		return;
	}

	glfwMakeContextCurrent(window);
}


Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::WindowSizeCallback(GLFWwindow * window, int width, int height)
{
	sizeCallback(sizeCallbackContext, width, height);
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

GLFWwindow * Window::GetHandle() const
{
	return window;
}

void Window::SetWindowResizeCallback(void * context, WindowSizeFN callback)
{
	sizeCallbackContext = context;
	sizeCallback = callback;
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
}

void Window::SetTitle(std::string title)
{
	glfwSetWindowTitle(window, title.c_str());
}

bool Window::IsInitialized() const
{
	return static_cast<bool>(window);
}

bool Window::ShouldWindowClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::PollEvents() const
{
	glfwPollEvents();
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(window);
}
