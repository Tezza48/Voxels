#pragma once
#include "Scene.h"
#include "Mesh.h"
#include "Texture3D.h"
#include "GraphicsShader.h"
#include "ComputeShader.h"
#include <chrono>

class Noise3DComputeScene :
	public Scene
{
private:
	Texture3D * noiseTexture;
	ComputeShader * noiseCompute;
	Mesh * spriteMesh;
	GraphicsShader * texColorShader;

	glm::vec3 eyePos;
	glm::vec3 eyeDir;

	std::chrono::high_resolution_clock::time_point startTime;
public:
	Noise3DComputeScene();
	~Noise3DComputeScene();

	// Inherited via Scene
	virtual void Start(Window & window, Renderer & renderer) override;
	virtual void Draw(Window & window, Renderer & renderer) override;
};

