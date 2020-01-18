#pragma once
#include "Renderer.h"
#include "Window.h"

class Scene
{
public:
	Scene();
	Scene(const Scene & scene) = delete;
	virtual ~Scene();

	virtual void Start(Window & window, Renderer & renderer) = 0;
	virtual void Draw(Window & window, Renderer & renderer) = 0;
};

