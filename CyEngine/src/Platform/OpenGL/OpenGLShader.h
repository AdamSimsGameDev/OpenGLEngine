#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/Renderer/Shader.h"

namespace Cy
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const String& vertex, const String& fragment);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformVec3(const String& name, const Vector3& vector) override;
		virtual void UploadUniformVec4(const String& name, const Vector4& vector) override;

		virtual void UploadUniformMat4(const String& name, const glm::mat4x4& matrix) override;

	private:
		uint32_t m_RendererId;
	};
}