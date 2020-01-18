#pragma once


#define ASSERT_NO_GL_ERRORS {\
	auto err = glGetError();\
	if (err != GLEW_OK) {\
		auto str = glewGetErrorString(err);\
		__debugbreak();\
	}\
}

#define PI 3.1416f

#define SAFE_DELETE(x) if (x) { delete x; x = nullptr; }