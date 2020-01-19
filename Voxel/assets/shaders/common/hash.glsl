#ifndef HASH
#define HASH

// Generate a random value from a vec3.
float hash31(vec3 p)
{
	return fract(sin(dot(p, vec3(302.672, 8861.772, 78123.71))) * 6614.7712);
}

#endif
