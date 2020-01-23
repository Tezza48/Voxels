float sdSphere(vec3 p, float r)
{
	return length(p) - r;
}

float sdPlane(vec3 p, vec3 n, float h)
{
	return dot(p, n) - h;
}

// iq
float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}