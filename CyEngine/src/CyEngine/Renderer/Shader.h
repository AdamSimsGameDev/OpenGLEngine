#pragma once
#include <CyEngine/String.h>
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
	
		static Shader* CreateFromFiles(const String& vertexPath, const String& fragmentPath);
		static Shader* Create(const String& vertexSrc, const String& fragmentSrc);

		virtual void UploadUniformVec3(const String& name, const glm::vec3& vector) = 0;
		virtual void UploadUniformMat4(const String& name, const glm::mat4& matrix) = 0;

	private:
		static void ParseShader(const String& filePath, String& outSource);
	};
}