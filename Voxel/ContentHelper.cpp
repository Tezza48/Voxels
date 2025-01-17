#define STB_IMAGE_IMPLEMENTATION

#if DEBUG || _DEBUG
#define STBI_FAILURE_USERMSG
#else
#define STBI_NO_FAILURE_STRINGS
#endif

#include "vendor/stb_image.h"

#include "ContentHelper.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <regex>
#include <filesystem>


using std::string;
using std::ifstream;
using std::stringstream;
using std::regex;
using std::cout;
using std::endl;

namespace fs = std::filesystem;

// Load a source file and reccursively replace includes with the right file.
std::string ContentHelper::LoadShaderSource(const std::string & path)
{
	const auto homeDir = fs::absolute(path).remove_filename();

	auto headFile = ReadFile(path);

	regex includeRegex = regex::basic_regex("(?:#pragma include<\")(.+)\">");
	std::smatch matches;

	while (std::regex_search(headFile, matches, includeRegex))
	{
		auto includeFilename = matches[1].str();

		auto includePath = homeDir.string() + includeFilename;

		string includedFile = LoadShaderSource(includePath);

		headFile = std::regex_replace(headFile, regex::basic_regex(matches[0].str()), includedFile);
	}

	return headFile;
}

string ContentHelper::ReadFile(const string & path)
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

unsigned char * ContentHelper::LoadTextureFile(const std::string & path, int * width, int * height, PixelFormat * bitsPerPixel)
{
	stbi_set_flip_vertically_on_load(true);
	int bpp;

	auto pathCstr = path.c_str();

	auto data = stbi_load(pathCstr, width, height, &bpp, STBI_rgb_alpha);

	auto failureReason = stbi_failure_reason();

	if (failureReason)
	{
		cout << failureReason << endl;
	}

	*bitsPerPixel = static_cast<PixelFormat>(bpp - 1);

	return data;
}

void ContentHelper::CleanupTextureFile(unsigned char * textureData)
{
	stbi_image_free(textureData);
}
