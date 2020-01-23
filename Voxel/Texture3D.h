#pragma once
#include "Texture.h"

class Texture3D :
	public Texture
{
private:
	int width;
	int height;
	int depth;

public:
	Texture3D(int width, int height, int depth, PixelFormat format);

	void SetEmpty();

	// Inherited via Texture
	virtual void SetupParamaters() override;
};