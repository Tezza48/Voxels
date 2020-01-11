#version 460

#define PI 3.14159

layout(location = 0) uniform vec2 iResolution;
layout(location = 1) uniform float iTime;

in vec2 fragCoord;

out vec4 color;

// Generate a random value from a vec2.
float hash21(vec2 p)
{
	return fract(sin(dot(p, vec2(302.672, 8861.772))) * 6614.7712);
}

// Generate a random value from a vec3.
float hash31(vec3 p)
{
	return fract(sin(dot(p, vec3(302.672, 8861.772, 78123.71))) * 6614.7712);
}

// Ease the components of a normalized genType using a cosine function.
#define cosEase(a) (1.0 - cos(a * PI)) / 2

// Generate Value noise from a vec2.
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

	lerpFactor = cosEase(lerpFactor);

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

// Generate fractal value noise from a vec2.
float fractalValueNoise21(vec2 p)
{
	float value = 0;
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

float map(vec3 p)
{
//	float res = length(p - vec3(0, 0, 10)) - 1.0;
//	return min(res, 4.0 * valueNoise31(p));
//	return p.y;
	return p.y - (fractalValueNoise31(vec3(p.xz / 4.0, iTime)) * 4.0);
}

#define MAX_STEPS 128
#define MAX_DIST 100

float trace(vec3 ro, vec3 rd)
{
	float t = 0.1;

	for (int i = 0; i < MAX_STEPS; i++)
	{
		if (t < 0 || t > MAX_DIST) break;

		vec3 p = ro + rd * t;
		float d = map(p);
		t += d;
	}

	return t;
}

vec3 calcNormal(vec3 p)
{
	vec2 h = vec2(0.0001, 0);
	float d = map(p);
	return normalize(vec3(
		map(p + h.xyy) - d,
		map(p + h.yxy) - d,
		map(p + h.yyx) - d)
	);
}

void main() {
	vec2 uv = fragCoord;
	uv.x *= iResolution.x/iResolution.y;

	vec3 ro = vec3(0, 4, 0);
	vec3 rd = normalize(vec3(uv, 1.0));

	float a = iTime / 4.0;

	float s = sin(a), c = cos(a);

	rd.xz *= mat2(c, -s, s, c);

	float t = trace(ro, rd);

	if (t > MAX_DIST)
	{
		color = vec4(0, 0, 0, 1);
		return;
	}

	vec3 norm = calcNormal(ro + rd * t);



	color = vec4(norm, 1);
}