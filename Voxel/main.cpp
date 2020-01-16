//#define GLEW_STATIC

#include <GL/glew.h>
#include <string>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <regex>

#include "common.h"
#include "GraphicsShader.h"
#include "LayoutDescription.h"
#include "Window.h"
#include "Renderer.h"
#include "Mesh.h"

#define PI 3.1416f

using namespace glm;

using std::string;
using std::ifstream;
using glm::value_ptr;
using std::stringstream;
using std::getline;
using std::chrono::high_resolution_clock;

string ReadFile(const string path);

int main(int argc, char ** argv)
{
	Window window(1600, 900, "Voxels");

	if (!window.IsInitialized()) {
		return 0;
	}

	Renderer renderer(window);

	//struct VertexPos2DTex
	//{
	//	vec2 pos;
	//	vec2 tex;
	//};

	//LayoutDescription layout2DGeom[2] = {
	//	{ 0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPos2DTex), (void *)offsetof(VertexPos2DTex, pos) },
	//	{ 1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPos2DTex), (void *)offsetof(VertexPos2DTex, tex) }
	//};

	//Mesh quadMesh(layout2DGeom, 2, 1);

	//VertexPos2DTex vertices[6] = {
	//	{ vec2(-1, -1), vec2(0, 0) },
	//	{ vec2(-1, 1), vec2(0, 1) },
	//	{ vec2(1, -1), vec2(1, 0) },
	//	{ vec2(1, 1), vec2(1, 1) },
	//};

	//unsigned int indices[6] = {
	//	0, 1, 2, 1, 2, 3
	//};

	//quadMesh.Bind();
	//quadMesh.SetVertices(reinterpret_cast<float *>(vertices), sizeof(VertexPos2DTex), sizeof(vertices));
	//quadMesh.SetIndices(0, indices, sizeof(indices));
	//quadMesh.SetIndices(0, indices, sizeof(indices));
	//quadMesh.Unbind();

	struct VertexPos2DColorTex
	{
		vec2 pos;
		vec4 color;
		vec2 texcoord;
	};

	std::array<LayoutDescription, 3> layout2DColorTex;
	layout2DColorTex[0] = { 0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPos2DColorTex), (void*)offsetof(VertexPos2DColorTex, pos) };
	layout2DColorTex[1] = { 1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPos2DColorTex), (void*)offsetof(VertexPos2DColorTex, color) };
	layout2DColorTex[2] = { 2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPos2DColorTex), (void*)offsetof(VertexPos2DColorTex, texcoord) };

	Mesh spriteMesh(layout2DColorTex, 1);

	std::array<VertexPos2DColorTex, 4> vertices;
	vertices[0] = { vec2(-0.5, -0.5), vec4(1, 0, 0, 1), vec2(0, 0) };
	vertices[1] = { vec2(-0.5, 0.5),  vec4(0, 1, 0, 1), vec2(0, 1) };
	vertices[2] = { vec2(0.5, -0.5),  vec4(0, 0, 1, 1), vec2(1, 0) };
	vertices[3] = { vec2(0.5, 0.5),   vec4(1, 1, 1, 1), vec2(1, 1) };

	unsigned int indices[6] = {
		0, 1, 2, 1, 2, 3
	};

	spriteMesh.Bind();
	spriteMesh.SetVertices(vertices);
	spriteMesh.SetIndices(0, indices, sizeof(indices));
	spriteMesh.Unbind();

	// Shader
	const GraphicsShader shader(
		ReadFile("./assets/shaders/tex.vert"),
		ReadFile("./assets/shaders/tex.frag"));

	auto startTime = high_resolution_clock::now();

	renderer.SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	auto projMat = glm::perspectiveFov(PI / 2.0f, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()), 0.01f, 100.0f);
	auto viewMat = glm::lookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));

	while (!window.ShouldWindowClose())
	{
		renderer.Clear();

		shader.Bind();

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - startTime);
		auto milliseconds = static_cast<float>(duration.count()) / 1000.0f;

		//glUniform2f(0, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()));
		//glUniform1f(1, milliseconds);

		renderer.DrawMesh(spriteMesh, viewMat, projMat);
		//renderer.DrawMesh(quadMesh, glm::mat4(0), glm::mat4(0));

		shader.Unbind();

		renderer.SwapBuffers();

		window.PollEvents();
	}

	return 0;
}

string ReadFile(const string path)
{
	ifstream ifs = ifstream(path.c_str());
	string line;

	stringstream fileDataStream;

	if (ifs.is_open())
	{
		while (getline(ifs, line))
		{
			fileDataStream << line << std::endl;
		}
	}
	else
	{
		std::cout << "Could not open file: " << path << std::endl;
	}

	ifs.close();

	return fileDataStream.str();
}

//string PreprocessGLSL(const string source)
//{
//	// Check for imports
//	std::smatch matches;
//	std::regex reg("(?:#pragma include<\")(. + )\">");
//
//	while (std::regex_search(source, matches, reg))
//	{
//		if (matches.ready())
//		{
//			std::cout << matches.str() << std::endl;
//		}
//	}
//
//	return source;
//}