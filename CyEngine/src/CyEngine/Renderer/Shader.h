#pragma once
#include <string>

namespace Cy
{
	class Shader
	{
	public:
		virtual ~Shader() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		static Shader* CreateFromFiles(const std::string& vertexPath, const std::string& fragmentPath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		static void ParseShader(const std::string& filePath, std::string& outSource);
	};
}