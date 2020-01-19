#ifndef EASE
#define EASE

#define PI 3.141

float cosEase(float a)
{
	return (1 - cos(a * PI)) / 2;
}

vec2 cosEase(vec2 a)
{
	return (1 - cos(a * PI)) / 2;
}

vec3 cosEase(vec3 a)
{
	return (1 - cos(a * PI)) / 2;
}

#endif