#include "Noise3DComputeScene.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "common.h"
#include "ContentHelper.h"

using namespace glm;
using namespace std::chrono;


Noise3DComputeScene::Noise3DComputeScene()
{
	spriteMesh = nullptr;
	noiseTexture = nullptr;
	noiseCompute = nullptr;
	texColorShader = nullptr;
}


Noise3DComputeScene::~Noise3DComputeScene()
{
	SAFE_DELETE(spriteMesh);
	SAFE_DELETE(noiseTexture);
	SAFE_DELETE(noiseCompute);
	SAFE_DELETE(texColorShader);
}

void Noise3DComputeScene::Start(Window & window, Renderer & renderer)
{
	struct VertexPos2DColorTex
	{
		vec2 pos;
		vec4 color;
		vec2 texcoord;
	};

	std::array<LayoutDescription, 3> layout2DColorTex;
	layout2DColorTex[0] = { 0, 2, LayoutDescription::Float, false, sizeof(VertexPos2DColorTex), (void*)offsetof(VertexPos2DColorTex, pos) };
	layout2DColorTex[1] = { 1, 4, LayoutDescription::Float, false, sizeof(VertexPos2DColorTex), (void*)offsetof(VertexPos2DColorTex, color) };
	layout2DColorTex[2] = { 2, 2, LayoutDescription::Float, false, sizeof(VertexPos2DColorTex), (void*)offsetof(VertexPos2DColorTex, texcoord) };

	spriteMesh = new Mesh(layout2DColorTex, 1);

	std::array<VertexPos2DColorTex, 4> vertices;
	vertices[0] = { vec2(-1, -1), vec4(1, 0, 0, 1), vec2(0, 0) };
	vertices[1] = { vec2(-1, 1),  vec4(0, 1, 0, 1), vec2(0, 1) };
	vertices[2] = { vec2(1, -1),  vec4(0, 0, 1, 1), vec2(1, 0) };
	vertices[3] = { vec2(1, 1),   vec4(1, 1, 1, 1), vec2(1, 1) };

	unsigned int indices[6] = {
		0, 1, 2, 1, 2, 3
	};

	spriteMesh->Bind();
	spriteMesh->SetVertices(vertices);
	spriteMesh->SetIndices(0, indices, 6);
	spriteMesh->Unbind();

	const int noiseMapWidth = 512;

	noiseTexture = new Texture3D(noiseMapWidth, noiseMapWidth, noiseMapWidth, PixelFormat::R);
	noiseTexture->Bind();
	noiseTexture->SetEmpty();

	noiseCompute = new ComputeShader(ContentHelper::LoadShaderSource("./assets/shaders/compute/computeNoise3D.comp"));
	noiseCompute->Bind();

	noiseCompute->BindImageTexture(noiseTexture, WriteOnly, 0);
	noiseCompute->SetUniform1i("writer", 0);
	noiseCompute->Dispatch(noiseMapWidth / 16, noiseMapWidth / 16, noiseMapWidth);
	noiseCompute->Unbind();

	// Shader
	texColorShader = new GraphicsShader(
		ContentHelper::ReadFile("./assets/shaders/graphics/tex3DSample.vert"),
		ContentHelper::ReadFile("./assets/shaders/graphics/tex3DSample.frag"));

	startTime = high_resolution_clock::now();
}

void Noise3DComputeScene::Draw(Window & window, Renderer & renderer)
{
	texColorShader->Bind();

	auto time = static_cast<float>(duration_cast<milliseconds>(startTime - high_resolution_clock::now()).count()) / 1000;

	texColorShader->SetUniform1f("uTime", time);

	const auto texSampler = 0;
	renderer.SetTextureSampler(texSampler, noiseTexture);
	texColorShader->SetUniform1i("uNoiseTexture", texSampler);

	renderer.DrawMesh(*spriteMesh, identity<mat4>(), identity<mat4>());

	texColorShader->Unbind();
}
