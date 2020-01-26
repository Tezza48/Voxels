#ifndef EASE
#define EASE

#define PI 3.141

#define COS_EASE(a) (1.0 - cos(a * PI)) / 2.0

float cosEase(float a)
{
	return COS_EASE(a);
}

vec2 cosEase(vec2 a)
{
	return COS_EASE(a);
}

vec3 cosEase(vec3 a)
{
	return COS_EASE(a);
}

#endif