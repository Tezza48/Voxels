#pragma once
#include <GL/glew.h>
#include <vector>
#include "LayoutDescription.h"
#include "IBindableResource.h"

class Mesh :
	IBindableResource
{
private:
	GLuint vertexArray;

	int numVertices;
	GLuint vertexBuffer;

	int numIndexBuffers;
	std::vector<GLuint> indexBuffers;
	std::vector<int> indexBufferSizes;

public:
	Mesh(const Mesh &) = delete;
	Mesh(LayoutDescription * layouts, int numLayouts, int numIndexBuffers = 0);
	~Mesh();

	const int GetNumVertices() const;
	const int GetNumIndexBuffers() const;

	const std::pair<GLuint, int> GetIndexBuffer(int index) const;

	// Inherited via IBindableResource
	void Bind() const;
	void Unbind() const;

	void SetVertices(float * vertexData, int size, int numVertices);

	void SetIndices(int buffer, unsigned int * indexData, int size);
};

