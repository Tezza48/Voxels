#pragma once
#include "Texture.h"

class Texture2D :
	public Texture
{
private:
	int width;
	int height;

public:
	Texture2D(int width, int height, PixelFormat format);

	void SetEmpty();
};