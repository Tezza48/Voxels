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
#include "Noise3DComputeScene.h"

using namespace glm;

using std::string;
using std::ifstream;
using glm::value_ptr;
using std::stringstream;
using std::getline;
using std::chrono::high_resolution_clock;

int main(int argc, char ** argv)
{
	Window window(800, 600, "Voxels");

	if (!window.IsInitialized()) {
		return 0;
	}

	Renderer renderer(window);

	Noise3DComputeScene scene;

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