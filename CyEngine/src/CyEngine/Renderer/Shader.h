#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

		virtual void UploadUniformVec3(const std::string& name, const glm::vec3& vector) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

	private:
		static void ParseShader(const std::string& filePath, std::string& outSource);
	};
}