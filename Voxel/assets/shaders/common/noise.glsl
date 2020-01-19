#ifndef NOISE
#define NOISE

vec3 cosEase(vec3);
float hash31(vec3);

#pragma include<"hash.glsl">
#pragma include<"ease.glsl">

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

// Generate fractal value noise from a vec3.
float fractalValueNoise31(vec3 p)
{
	float value = 0;
	float amp = 0.5;

	for (int i = 0, l = 3; i < l; i++)
	{
		value += valueNoise31(p) * amp;
		amp *= 0.5;
		p *= 2;
	}

	return value;
}
#endif