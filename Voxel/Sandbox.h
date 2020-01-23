#pragma once
#include "Scene.h"
#include <glm/glm.hpp>
#include "ComputeShader.h"
#include "Texture2D.h"
#include <chrono>

class Sandbox :
	public Scene
{
private:
	Texture2D * raymarchRenderTexture;
	Texture2D * raymarchLightmap;
	ComputeShader * raymarchShader;

	std::chrono::high_resolution_clock::time_point startTime;

public:
	Sandbox();
	~Sandbox();

	// Inherited via Scene
	virtual void Start(Window & window, Renderer & renderer) override;
	virtual void Draw(Window & window, Renderer & renderer) override;
};

