#pragma once
#include <GL/glew.h>
#include <vector>
#include "LayoutDescription.h"
#include "RendererResource.h"
#include <array>

// Contains all data for the renderer to be able to render a Mesh.
class Mesh :
	RendererResource
{
private:
	// OpenGL Vertex Array Object.
	GLuint vertexArray;

	// Number of vertices in this mesh.
	int numVertices;
	// OpenGL Vertex Buffer Object. 
	GLuint vertexBuffer;

	// TODO: Investigate using one index buffer with offsets for static batching a scene.

	// Number of Index Buffers. (allows multiple meshes to belong in the vertex buffer);
	int numIndexBuffers;

	// Array of Index Buffers.
	std::vector<GLuint> indexBuffers;

	// Array of the sizes of the index buffers in `indexBuffers`.
	std::vector<int> indexBufferSizes;

public:
	// Delete the Copy ctor.
	Mesh(const Mesh &) = delete;

	// Create an instance of `Mesh`.
	template<int _C>
	Mesh(std::array<LayoutDescription, _C> & layouts, int numIndexBuffers = 0);

	~Mesh();

private:
	// Constructor which sets up the VAO, VBO and any Index Buffers.
	Mesh(LayoutDescription * layouts, int numLayouts, int numIndexBuffers = 0);


public:
	// Set the vertices of this mesh.
	template<typename T, int _C>
	void SetVertices(std::array<T, _C> & vertexData);

	// Set the indices of index buffer `buffer` with the provided data.
	void SetIndices(int buffer, unsigned int * indexData, int size);

	// Get the number of vertices in this mesh.
	const int GetNumVertices() const;

	// Get the number of index buffers in this mesh.
	const int GetNumIndexBuffers() const;

	// Returns the requested index buffer and it's size.
	const std::pair<GLuint, int> GetIndexBuffer(int index) const;

	// Inherited via IBindableResource
	void Bind() const;
	void Unbind() const;
	
private:
	// Set the vertices of this mesh.
	void SetVertices(void * vertexData, int size, int numVertices);
};

template<int _C>
inline Mesh::Mesh(std::array<LayoutDescription, _C> & layouts, int numIndexBuffers): Mesh(layouts.data(), _C, numIndexBuffers)
{
}

template<typename T, int _C>
inline void Mesh::SetVertices(std::array<T, _C> & vertexData)
{
	SetVertices(static_cast<void *>(vertexData.data()), sizeof(T), _C);
}
