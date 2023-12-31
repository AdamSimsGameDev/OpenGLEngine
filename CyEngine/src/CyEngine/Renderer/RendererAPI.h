#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "CyEngine/Maths/Colour.h"

namespace Cy
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void SetClearColour(const Colour& colour) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}