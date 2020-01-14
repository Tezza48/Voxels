#pragma once

#define GLFW_DLL

#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
	GLFWwindow * window;

	int width;
	int height;

public:
	Window() = delete;

	Window(int width, int height, std::string title);
	~Window();

	int GetWidth() const;
	int GetHeight() const;

	GLFWwindow * GetHandle() const;

	void SetTitle(std::string title);

	bool IsInitialized() const;

	bool ShouldWindowClose() const;

	void PollEvents() const;

	void SwapBuffers() const;
};

