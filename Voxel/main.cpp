#include <Windows.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <chrono>
#include "common.h"
#include "GraphicsShader.h"
#include "LayoutDescription.h"
#include "Window.h"
#include "Renderer.h"
#include "Mesh.h"
#include "ComputeShader.h"
#include "Texture2D.h"
#include "SpriteTestScene.h"
#include <iostream>

using namespace glm;

using std::string;
using std::ifstream;
using glm::value_ptr;
using std::stringstream;
using std::getline;
using std::chrono::high_resolution_clock;

int main(int argc, char** argv)
{
#if DEBUG || _DEBUG
	for (auto i = 0, l = argc - 1; i < l; i++)
	{
		if (string(argv[i]) == "/r") {
			SetCurrentDirectory(argv[i + 1]);
			break;
		}
	}

	auto buffLen = GetCurrentDirectory(0, 0);
	char * dir = new char[buffLen];
	auto ret = GetCurrentDirectory(buffLen, dir);

	std::cout << dir << std::endl << argv[0] << std::endl;

#endif

	Window window(800, 600, "Voxels");

	if (!window.IsInitialized()) {
		return 0;
	}

	Renderer renderer(window);

	SpriteTestScene scene;

	renderer.SetClearColor({ 0.1f, 0.1f, 0.3f, 1.0f });

	scene.Start(window, renderer);

	while (!window.ShouldWindowClose())
	{
		renderer.Clear();

		scene.Draw(window, renderer);

		renderer.SwapBuffers();

		window.PollEvents();
	}

	return 0;
}