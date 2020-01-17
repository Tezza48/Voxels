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
#include "ComputeShader.h"

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
	spriteMesh.SetIndices(0, indices, 6);
	spriteMesh.Unbind();

	GLuint noiseTexture = 0;
	glCreateTextures(GL_TEXTURE_2D, 1, &noiseTexture);
	glBindTexture(GL_TEXTURE_2D, noiseTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	const int noiseMapWidth = 64;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, noiseMapWidth, noiseMapWidth, 0, GL_RED, GL_FLOAT, nullptr);
	
	glBindImageTexture(0, noiseTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R8);

	const ComputeShader noiseCompute(ReadFile("./assets/shaders/compute.comp"));
	noiseCompute.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, noiseTexture);

	noiseCompute.SetUniform1i("writer", 0);
	noiseCompute.Dispatch(noiseMapWidth / 16, noiseMapWidth / 16, 1);
	noiseCompute.Unbind();

	// Shader
	const GraphicsShader shader(
		ReadFile("./assets/shaders/tex.vert"),
		ReadFile("./assets/shaders/tex.frag"));

	auto startTime = high_resolution_clock::now();

	renderer.SetClearColor({ 0.1f, 0.1f, 0.3f, 1.0f });

	auto projMat = glm::perspectiveFov(PI / 2.0f, static_cast<float>(window.GetWidth()), static_cast<float>(window.GetHeight()), 0.01f, 100.0f);
	auto viewMat = glm::lookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));

	while (!window.ShouldWindowClose())
	{
		renderer.Clear();

		shader.Bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, noiseTexture);

		shader.SetUniform1i("uNoiseTexture", 0);

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - startTime);
		auto milliseconds = static_cast<float>(duration.count()) / 1000.0f;

		shader.SetUniform1f("uTime", milliseconds);

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