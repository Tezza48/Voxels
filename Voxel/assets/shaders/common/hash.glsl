#ifndef HASH
#define HASH

// Generate a random value from a vec2.
float hash21(vec2 p)
{
	return fract(sin(dot(p, vec2(302.672, 8861.772))) * 6614.7712);
}

// Hash without Sine 2 - https://www.shadertoy.com/view/XdGfRR
#define UI0 1597334673U
#define UI1 3812015801U
#define UI2 uvec2(UI0, UI1)
#define UI3 uvec3(UI0, UI1, 2798796415U)
#define UIF (1.0 / float(0xffffffffU))

vec2 hash22(vec2 p)
{
	uvec2 q = uvec2(ivec2(p))*UI2;
	q = (q.x ^ q.y) * UI2;
	return vec2(q) * UIF;
}

// Generate a random value from a vec3.
float hash31(vec3 p)
{
	return fract(sin(dot(p, vec3(302.672, 8861.772, 78123.71))) * 6614.7712);
}

#endif
