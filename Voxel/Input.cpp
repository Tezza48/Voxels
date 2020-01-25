#include "Input.h"

Input::KeyMap Input::liveKeyState;
Input::KeyMap Input::thisKeyState;
Input::KeyMap Input::lastKeyState;

void Input::Init(Window & window)
{
	glfwSetKeyCallback(window.GetHandle(), KeyCallback);

	thisKeyState = KeyMap();
	lastKeyState = KeyMap();
	liveKeyState = KeyMap();
}

void Input::Update()
{
	std::copy(thisKeyState.begin(), thisKeyState.end(), &lastKeyState);
	std::copy(liveKeyState.begin(), liveKeyState.end(), &thisKeyState);
}

bool Input::GetKey(Key key)
{
	return thisKeyState[key];
}

void Input::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	liveKeyState[key] = (action == GLFW_PRESS);
}
