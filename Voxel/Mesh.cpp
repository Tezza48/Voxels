#include "Mesh.h"
#include "common.h"

using std::vector;

Mesh::Mesh(LayoutDescription * layouts, int numLayouts, int numIndexBuffers): numIndexBuffers(numIndexBuffers)
{
	glGenVertexArrays(1, &vertexArray);
	Bind();

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	indexBuffers = vector<GLuint>(numIndexBuffers);
	indexBufferSizes = vector<int>(numIndexBuffers);
	glGenBuffers(numIndexBuffers, indexBuffers.data());

	for (size_t i = 0, l = numLayouts; i < l; i++) {
		auto layout = layouts[i];

		glEnableVertexAttribArray(layout.index);
		glVertexAttribPointer(layout.index, layout.size, layout.type, layout.normalized, layout.stride, layout.pointer);
	}

	Unbind();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArray);
}

const int Mesh::GetNumVertices() const
{
	return numVertices;
}

const int Mesh::GetNumIndexBuffers() const
{
	return numIndexBuffers;
}

const std::pair<GLuint, int> Mesh::GetIndexBuffer(int index) const
{
	return std::pair<GLuint, int>(indexBuffers[index], indexBufferSizes[index]);
}

void Mesh::Bind() const
{
	glBindVertexArray(vertexArray);
}

void Mesh::Unbind() const
{
	glBindVertexArray(0);
}

void Mesh::SetVertices(void * vertexData, int vertexSize, int numVertices)
{
	this->numVertices = numVertices;

	glBufferData(GL_ARRAY_BUFFER, vertexSize * numVertices, vertexData, GL_STATIC_DRAW);
}

void Mesh::SetName(std::string name)
{
	Bind();

	auto vaoName = "Mesh(" + name + "_VertexArray)";
	glObjectLabel(GL_VERTEX_ARRAY, vertexArray, vaoName.length(), vaoName.c_str());

	auto vBufferName = "Mesh(" + name + "_VertexBuffer)";
	glObjectLabel(GL_ARRAY_BUFFER, vertexBuffer, vBufferName.length(), vBufferName.c_str());

	Unbind();

	for (int i = 0, l = indexBuffers.size(); i < l; i++)
	{
		auto iBufferName = "Mesh(" + name + "_IndexBuffer_" + std::to_string(i) + ")";
		auto iBuffer = GetIndexBuffer(i).first;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);
		glObjectLabel(GL_ELEMENT_ARRAY_BUFFER, iBuffer, iBufferName.length(), iBufferName.c_str());
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::SetIndices(int buffer, unsigned int * indexData, int size)
{
	indexBufferSizes[buffer] = size;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffers[buffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), indexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


