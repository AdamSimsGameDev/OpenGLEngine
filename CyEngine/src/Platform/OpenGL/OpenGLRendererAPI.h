#pragma once

#include "CyEngine/Renderer/RendererAPI.h"

namespace Cy
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColour(const glm::vec4& colour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
