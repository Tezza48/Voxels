#pragma once

#define GLFW_DLL

#include <GLFW/glfw3.h>
#include <string>

typedef void(*WindowSizeFN)(void* context, int width, int height);

class Window
{
private:
	GLFWwindow * window;

	int width;
	int height;

	static void * sizeCallbackContext;
	static WindowSizeFN sizeCallback;

public:
	Window() = delete;

	Window(int width, int height, std::string title);
	~Window();

	int GetWidth() const;
	int GetHeight() const;

	GLFWwindow * GetHandle() const;

	void SetWindowResizeCallback(void * context, WindowSizeFN callback);

	void SetTitle(std::string title);

	bool IsInitialized() const;

	bool ShouldWindowClose() const;

	void PollEvents() const;

	void SwapBuffers() const;

private:
	static void WindowSizeCallback(GLFWwindow * window, int width, int height);
};

