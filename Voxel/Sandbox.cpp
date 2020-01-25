#include "Sandbox.h"
#include "common.h"
#include "ContentHelper.h"
#include "Input.h"

using namespace ContentHelper;

using namespace std::chrono;

using glm::vec4;

Sandbox::Sandbox()
{
	raymarchShader = nullptr;
	raymarchRenderTexture = nullptr;
	raymarchLightmap = nullptr;
}

Sandbox::~Sandbox()
{
	SAFE_DELETE(raymarchShader);
	SAFE_DELETE(raymarchRenderTexture);
	SAFE_DELETE(raymarchLightmap);
}

void Sandbox::Start(Window & window, Renderer & renderer)
{
	raymarchRenderTexture = new Texture2D(window.GetWidth(), window.GetHeight(), PixelFormat::RGBA);
	raymarchRenderTexture->SetName("RaymarchTarget");

	raymarchLightmap = new Texture2D(window.GetWidth(), window.GetHeight(), PixelFormat::R);
	raymarchLightmap->SetName("RaymarchLightmap");

	raymarchShader = new ComputeShader(LoadShaderSource("./assets/shaders/compute/raymarch0.comp"));
	raymarchShader->SetName("RaymarchComputeShader");

	startTime = high_resolution_clock::now();
}

void Sandbox::Draw(Window & window, Renderer & renderer)
{
	const auto width = window.GetWidth();
	const auto height = window.GetHeight();

	auto time = static_cast<float>(duration_cast<milliseconds>(startTime - high_resolution_clock::now()).count()) / 1000;

	raymarchShader->Bind();
	raymarchShader->BindImageTexture(raymarchRenderTexture, ImageAccess::WriteOnly, 0);
	raymarchShader->BindImageTexture(raymarchLightmap, ImageAccess::WriteOnly, 1);
	raymarchShader->SetUniform1f("uTime", time);
	raymarchShader->Dispatch(width / 32, static_cast<int>(ceil(height / 32.0f)), 1);
	raymarchShader->Unbind();

	renderer.DrawTexture(raymarchRenderTexture, vec4(0, 0, width, height));
}
