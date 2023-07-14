#include "cypch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Cy
{
	Shader* Shader::CreateFromFiles(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertex, fragment;
		ParseShader(vertexPath, vertex);
		ParseShader(fragmentPath, fragment);
		return Create(vertex, fragment);
	}

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}

	void Shader::ParseShader(const std::string& filePath, std::string& outSource)
	{
		std::ifstream stream(filePath);
		std::string line;
		std::stringstream ss;
		while (getline(stream, line))
		{
			ss << line << '\n';
		}
		outSource = ss.str();
	}

}
