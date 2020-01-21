#pragma once
#include "Scene.h"
#include "Texture2D.h"

class SpriteTestScene :
	public Scene
{
private:
	Texture2D * spriteTexture;

public:
	SpriteTestScene();
	~SpriteTestScene();

	// Inherited via Scene
	virtual void Start(Window & window, Renderer & renderer) override;
	virtual void Draw(Window & window, Renderer & renderer) override;
};

