#ifndef NOISE
#define NOISE

vec3 cosEase(vec3);
float hash31(vec3);
float hash21(vec2);
vec2 hash22(vec2);

#pragma include<"hash.glsl">
#pragma include<"ease.glsl">

float valueNoise21(vec2 p)
{
	vec2 lerpFactor = fract(p - 0.5);

	float c00, c10, c01, c11;

	if (lerpFactor.x >= 0.5) // use this cellPos and one to the right
	{
		p.x -= 1.0;
	}
	if (lerpFactor.y >= 0.5)
	{
		p.y -= 1.0;
	}

	lerpFactor = cosEase(lerpFactor.xyx).xy;

	c00 = hash21(floor((p + vec2(0, 0))));
	c10 = hash21(floor((p + vec2(1, 0))));

	c01 = hash21(floor((p + vec2(0, 1))));
	c11 = hash21(floor((p + vec2(1, 1))));
	
	float bottom = mix(c00, c10, lerpFactor.x);
	float top = mix(c01, c11, lerpFactor.x);

	return mix(bottom, top, lerpFactor.y);
}

// Generate value noise from a vec3.
float valueNoise31(vec3 p)
{
	vec3 lerpFactor = fract(p - 0.5);

	float	c000, c100,
			c010, c110,
			c001, c101,
			c011, c111;

	// TODO: Figure a way to remove these branches (slower than it could be)
	if (lerpFactor.x >= 0.5) // use this cellPos and one to the right
	{
		p.x -= 1.0;
	}
	if (lerpFactor.y >= 0.5)
	{
		p.y -= 1.0;
	}
	if (lerpFactor.z >= 0.5)
	{
		p.z -= 1.0;
	}

	lerpFactor = cosEase(lerpFactor);

	// front plane
	// bottom line
	c000 = hash31(floor((p + vec3(0, 0, 0))));
	c100 = hash31(floor((p + vec3(1, 0, 0))));

	float fbottom = mix(c000, c100, lerpFactor.x);

	// top line
	c010 = hash31(floor((p + vec3(0, 1, 0))));
	c110 = hash31(floor((p + vec3(1, 1, 0))));
	
	float ftop = mix(c010, c110, lerpFactor.x);

	float front = mix(fbottom, ftop, lerpFactor.y);

	// back plane
	// bottom line
	c001 = hash31(floor((p + vec3(0, 0, 1))));
	c101 = hash31(floor((p + vec3(1, 0, 1))));

	float bbottom = mix(c001, c101, lerpFactor.x);

	// top line
	c011 = hash31(floor((p + vec3(0, 1, 1))));
	c111 = hash31(floor((p + vec3(1, 1, 1))));
	
	float btop = mix(c011, c111, lerpFactor.x);

	float back = mix(bbottom, btop, lerpFactor.y);

	return mix(front, back, lerpFactor.z);
}

// vec2 Voronoise
float voronoise21(vec2 p)
{
    vec2 cellPos = fract(p);
    vec2 cellId = floor(p);
    
    float len = 2.0;
    
    for (int y = -1; y < 2; y++)
    {
    	for (int x = -1; x < 2; x++)
        {
            vec2 offs = vec2(x, y);
            len = min(len, length(cellPos + offs - hash22(cellId - offs)));
        }
    }
    
    return len;
}

// Generate fractal value noise from a vec2.
float fractalValueNoise21(vec2 p)
{
	float value = 0.0;
	float amp = 0.5;

	for (int i = 0, l = 3; i < l; i++)
	{
		value += valueNoise21(p) * amp;
		amp *= 0.5;
		p *= 2;
	}

	return value;
}

// Generate fractal value noise from a vec3.
float fractalValueNoise31(vec3 p)
{
	float value = 0.0;
	float amp = 0.5;

	for (int i = 0, l = 3; i < l; i++)
	{
		value += valueNoise31(p) * amp;
		amp *= 0.5;
		p *= 2;
	}

	return value;
}

float fractalVoronoise21(vec2 p)
{
    float value = 0.0;
    float amp = 0.5;
    
    for(int i = 0; i < 6; i++)
    {
        value += voronoise21(p) * amp;
        amp *= 0.5;
		p *= 2;
    }

	return value;
}
#endif