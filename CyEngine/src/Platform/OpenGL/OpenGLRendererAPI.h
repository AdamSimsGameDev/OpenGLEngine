#pragma once

#include "CyEngine/Renderer/RendererAPI.h"

namespace Cy
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColour(const Colour& colour) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
