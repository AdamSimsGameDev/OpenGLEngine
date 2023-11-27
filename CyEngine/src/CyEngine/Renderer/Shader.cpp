#include "cypch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Cy
{
	Shader* Shader::CreateFromFiles(const String& vertexPath, const String& fragmentPath)
	{
		String vertex, fragment;
		ParseShader(vertexPath, vertex);
		ParseShader(fragmentPath, fragment);
		return Create(vertex, fragment);
	}

	Shader* Shader::Create(const String& vertexSrc, const String& fragmentSrc)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}

	void Shader::ParseShader(const String& filePath, String& outSource)
	{
		std::ifstream stream(filePath);
		std::string line;
		std::stringstream ss;
		while (getline(stream, line))
		{
			ss << line << '\n';
		}
		outSource = ss.str().c_str();
	}

}
