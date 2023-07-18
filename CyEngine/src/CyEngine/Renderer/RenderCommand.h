#pragma once

#include "CyEngine/Maths/Colour.h"
#include "RendererAPI.h"

namespace Cy
{
	class RenderCommand
	{
	public:
		inline static void SetClearColour(const Colour& colour)
		{
			s_RenderAPI->SetClearColour(colour);
		}

		inline static  void Clear()
		{
			s_RenderAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RenderAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RenderAPI;
	};
}
