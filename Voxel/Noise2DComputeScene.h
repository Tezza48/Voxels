#pragma once
#include "Scene.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "GraphicsShader.h"
#include "ComputeShader.h"

class Noise2DComputeScene :
	public Scene
{
private:
	Texture2D * noiseTexture;
	ComputeShader * noiseCompute;
	Mesh * spriteMesh;
	GraphicsShader * texColorShader;

	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;

public:
	Noise2DComputeScene();
	~Noise2DComputeScene();

	// Inherited via Scene
	virtual void Start(Window & window, Renderer & renderer) override;

	virtual void Draw(Window & window, Renderer & renderer) override;

};

