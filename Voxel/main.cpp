#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>

#if DEBUG || _DEBUG
#define GL_CALL(x) x;\
{\
	GLenum err;\
	while(1)\
	{\
		err = glGetError();\
		if (err == GL_NO_ERROR) break;\
		cout << glewGetErrorString(err) << " at " << __LINE__ <<  endl;\
	}\
}
#else
#define GL_CALL(x) x
#endif

using std::string;
using std::ifstream;
using glm::vec2;
using glm::value_ptr;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;

string ReadFile(const string path);

GLuint CreateShader(GLenum type, string source);

GLuint CreateProgram(string vertexSource, string fragmentSource);

int main(int argc, char ** argv)
{
	if (!glfwInit())
	{
		cout << "Failed to init glfw" << endl;
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(1600, 900, "Voxels", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		cout << "Failed to create Window" << endl;
		return 0;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	GLuint vao;
	GL_CALL(glCreateVertexArrays(1, &vao));
	GL_CALL(glBindVertexArray(vao));

	// Post Process quad
	GLuint vBuffer;
	GL_CALL(glGenBuffers(1, &vBuffer));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vBuffer));

	vec2 vertPos[6] = {
		vec2(-1, -1),
		vec2(-1, 1),
		vec2(1, -1),
		vec2(-1, 1),
		vec2(1, 1),
		vec2(1, -1),
	};

	GL_CALL(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), value_ptr(vertPos[0]), GL_STATIC_DRAW));

	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));

	// Shader
	const GLuint prog = CreateProgram("shader_vert.glsl", "shader_frag.glsl");

	GL_CALL(glUseProgram(prog));

	glUniform2f(0, 1600.0f, 900.0f);

	auto startTime = high_resolution_clock::now();

	while (!glfwWindowShouldClose(window))
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(high_resolution_clock::now() - startTime);
		auto milliseconds = static_cast<float>(duration.count()) / 1000.0f;

		glUniform1f(1, milliseconds);

		GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

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
			fileDataStream << line << endl;
		}
	}

	ifs.close();

	return fileDataStream.str();
}

// Create an OpenGL shader from the provided GLSL source code.
GLuint CreateShader(GLenum type, string source)
{
	const GLuint shader = glCreateShader(type);

	const char * cstrSource = source.c_str();
	const GLint lenSource = (GLint)source.length();

	GL_CALL(glShaderSource(shader, 1, &cstrSource, &lenSource));

	GL_CALL(glCompileShader(shader));

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		int logLength;
		GLchar log[1024];
		glGetShaderInfoLog(shader, 1024, &logLength, log);
		cout << "Shader Compile Error: " << log << endl;
	}

	return shader;
}

// Create an OpenGl Program from the provided GLSL source files.
GLuint CreateProgram(string vertexPath, string fragmentPath)
{
	GLuint vShader = CreateShader(GL_VERTEX_SHADER, ReadFile(vertexPath));
	GLuint fShader = CreateShader(GL_FRAGMENT_SHADER, ReadFile(fragmentPath));

	GLuint prog = glCreateProgram();
	GL_CALL(glAttachShader(prog, vShader));
	GL_CALL(glAttachShader(prog, fShader));

	GL_CALL(glLinkProgram(prog));

	GLint linkStatus;
	GL_CALL(glGetProgramiv(prog, GL_LINK_STATUS, &linkStatus));
	if (linkStatus != GL_TRUE)
	{
		int logLength;
		GLchar log[1024];
		glGetProgramInfoLog(prog, 1024, &logLength, log);
		cout << "Program Link Error: " << log << endl;
	}

	return prog;
}
