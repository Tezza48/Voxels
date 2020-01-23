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
	Texture2D(int width, int height, PixelFormat format, unsigned char * data);

	void SetEmpty();

protected:
	virtual void SetupParamaters() override;
};