#include "Noise2DComputeScene.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "common.h"
#include "ContentHelper.h"

using namespace glm;

Noise2DComputeScene::Noise2DComputeScene()
{
	spriteMesh = nullptr;
	noiseTexture = nullptr;
	noiseCompute = nullptr;
	texColorShader = nullptr;
}


Noise2DComputeScene::~Noise2DComputeScene()
{
	SAFE_DELETE(spriteMesh);
	SAFE_DELETE(noiseTexture);
	SAFE_DELETE(noiseCompute);
	SAFE_DELETE(texColorShader);
}

void Noise2DComputeScene::Start(Window & window, Renderer & renderer)
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
	vertices[0] = { vec2(-0.5, -0.5), vec4(1, 0, 0, 1), vec2(0, 0) };
	vertices[1] = { vec2(-0.5, 0.5),  vec4(0, 1, 0, 1), vec2(0, 1) };
	vertices[2] = { vec2(0.5, -0.5),  vec4(0, 0, 1, 1), vec2(1, 0) };
	vertices[3] = { vec2(0.5, 0.5),   vec4(1, 1, 1, 1), vec2(1, 1) };

	unsigned int indices[6] = {
		0, 1, 2, 1, 2, 3
	};

	spriteMesh->Bind();
	spriteMesh->SetVertices(vertices);
	spriteMesh->SetIndices(0, indices, 6);
	spriteMesh->Unbind();

	const int noiseMapWidth = 64;

	noiseTexture = new Texture2D(noiseMapWidth, noiseMapWidth, PixelFormat::R);
	noiseTexture->Bind();
	noiseTexture->SetEmpty();
	noiseTexture->Unbind();

	noiseCompute = new ComputeShader(ContentHelper::ReadFile("./assets/shaders/computeNoise2D.comp"));
	noiseCompute->Bind();

	noiseCompute->BindImageTexture(*noiseTexture, WriteOnly);
	noiseCompute->SetUniform1i("writer", 0);
	noiseCompute->Dispatch(noiseMapWidth / 16, noiseMapWidth / 16, 1);
	noiseCompute->Unbind();

	// Shader
	texColorShader = new GraphicsShader(
		ContentHelper::ReadFile("./assets/shaders/tex.vert"),
		ContentHelper::ReadFile("./assets/shaders/tex.frag"));

	projMatrix  = glm::perspectiveFov(PI / 2.0f, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()), 0.01f, 100.0f);
	viewMatrix  = glm::lookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));
}

void Noise2DComputeScene::Draw(Window & window, Renderer & renderer)
{
	texColorShader->Bind();

	const auto texSampler = 0;
	renderer.SetTextureSampler(texSampler, *noiseTexture);
	texColorShader->SetUniform1i("uNoiseTexture", texSampler);

	renderer.DrawMesh(*spriteMesh, viewMatrix, projMatrix);

	texColorShader->Unbind();
}
