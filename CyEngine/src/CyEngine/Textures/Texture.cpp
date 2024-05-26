#include "cypch.h"
#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Cy
{
	Texture::Texture(int width, int height, TextureFilterMode filterMode, TextureClampMode clampMode)
	{
		m_Width = width;
		m_Height = height;
		m_FilterMode = filterMode;
		m_ClampMode = clampMode;

		m_RendererId = 0;
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetFilterMode(TextureFilterMode fm)
	{
		m_FilterMode = fm;

		glBindTexture(GL_TEXTURE_2D, m_RendererId);

		switch (m_FilterMode)
		{
		case TextureFilterMode::Point:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_POINT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_POINT);
			break;
		case TextureFilterMode::Linear:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetClampMode(TextureClampMode cm)
	{
		m_ClampMode = cm;

		glBindTexture(GL_TEXTURE_2D, m_RendererId);

		switch (m_ClampMode)
		{
		case TextureClampMode::Clamp:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		case TextureClampMode::Repeat:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case TextureClampMode::Mirrored:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			break;
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture* Texture::LoadTexture(const String& path, TextureFilterMode filterMode, TextureClampMode clampMode)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(*path, &width, &height, &nrChannels, 0);
		if (!data)
		{
			CY_ERROR("Failed to load texture from path: %s", *path);
			return nullptr;
		}

		Texture* texture = new Texture(width, height, filterMode, clampMode);

		glGenTextures(1, &texture->m_RendererId);
		glBindTexture(GL_TEXTURE_2D, texture->m_RendererId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		texture->SetFilterMode(texture->m_FilterMode);
		texture->SetClampMode(texture->m_ClampMode);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		return texture;
	}
}
