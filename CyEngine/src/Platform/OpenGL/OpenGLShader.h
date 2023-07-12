#pragma once

#include "CyEngine/Renderer/Shader.h"

namespace Cy
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertex, const std::string& fragment);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererId;
	};
}