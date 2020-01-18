#pragma once

//#define GLFW_DLL

#include <GLFW/glfw3.h>
#include <string>

typedef void(*WindowSizeFN)(void* context, int width, int height);

class Window
{
private:
	// GLFW Window object.
	GLFWwindow * window;

	// Window's Width.
	int width;

	// Window's Height.
	int height;

	// Context for the window size callback function.
	static void * sizeCallbackContext;

	// Callback for when the window is resized.
	static WindowSizeFN sizeCallback;

public:
	// Delete the default ctor.
	Window() = delete;

	// Instantiate a window with this width, height and title.
	Window(int width, int height, std::string title);
	~Window();

	// Returns the width of this window.
	int GetWidth() const;

	// Returns the height of this window.
	int GetHeight() const;

	// Get the handle of this window.
	GLFWwindow * GetHandle() const;

	// Setup a callback for when this window is resized.
	void SetWindowResizeCallback(void * context, WindowSizeFN callback);

	// Set the title.
	void SetTitle(std::string title);

	// Check whether this is properly initialized.
	bool IsInitialized() const;

	// Check whether this window should close.
	bool ShouldWindowClose() const;

	// Poll all events for this window.
	void PollEvents() const;

	// Swap the Render buffers.
	void SwapBuffers() const;

private:
	// Static callback for the window Resize event. Calls sizeCallback with it's context.
	static void WindowSizeCallback(GLFWwindow * window, int width, int height);
};

