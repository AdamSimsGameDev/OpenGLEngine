#pragma once

#include "CyEngine/Core.h"

namespace Cy
{
	ENUM()
	enum class TextureFilterMode
	{
		Point,
		Linear
	};

	ENUM()
	enum class TextureClampMode
	{
		Clamp, 
		Repeat,
		Mirrored
	};

	class CY_API Texture
	{
	public:
		Texture(int width, int height, TextureFilterMode fm, TextureClampMode cm);

		void Bind();
		void Unbind();

		void SetFilterMode(TextureFilterMode fm);
		void SetClampMode(TextureClampMode cm);

		static Texture* LoadTexture(
			const String& path, 
			TextureFilterMode filterMode = TextureFilterMode::Linear, 
			TextureClampMode clampMode = TextureClampMode::Clamp
		);
	
	public:
		int m_Width;
		int m_Height;

		TextureFilterMode m_FilterMode;
		TextureClampMode m_ClampMode;

		uint32_t m_RendererId;
	};
}
