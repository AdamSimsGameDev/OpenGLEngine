#pragma once

#include "CyEngine/Core.h"

namespace Cy
{
	class CY_API Texture
	{
	public:
		Texture(int width, int height);

		void Bind();
		void Unbind();

		static Texture* LoadTexture(const String& path);
	
	public:
		int m_Width;
		int m_Height;

		uint32_t m_RendererId;
	};
}
