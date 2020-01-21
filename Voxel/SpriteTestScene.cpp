#include "SpriteTestScene.h"
#include "common.h"
#include "ContentHelper.h"

SpriteTestScene::SpriteTestScene()
{
	spriteTexture = nullptr;
}


SpriteTestScene::~SpriteTestScene()
{
	SAFE_DELETE(spriteTexture);
}

void SpriteTestScene::Start(Window & window, Renderer & renderer)
{
	int width, height;
	PixelFormat format;

	auto textureData = ContentHelper::LoadTextureFile("./assets/images/crate0_diffuse.png", &width, &height, &format);

	spriteTexture = new Texture2D(width, height, format, textureData);

	ContentHelper::CleanupTextureFile(textureData);
}

void SpriteTestScene::Draw(Window & window, Renderer & renderer)
{
	renderer.DrawTexture(spriteTexture, glm::vec4(0, 0, 500, 500));
}
