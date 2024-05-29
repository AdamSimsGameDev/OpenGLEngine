#pragma once
#include "CyEngine/Maths/Vector.h"
#include "CyEngine/Maths/Matrix.h"
#include "CyEngine/String.h"

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

		virtual void UploadUniformVec3(const String& name, const Vector3& vector) = 0;
		virtual void UploadUniformMat4(const String& name, const glm::mat4x4& matrix) = 0;

	private:
		static void ParseShader(const String& filePath, String& outSource);
	};
}