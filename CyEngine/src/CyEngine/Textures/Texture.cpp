#include "cypch.h"
#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Cy
{
	Texture::Texture(int width, int height)
	{
		m_Width = width;
		m_Height = height;
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

	Texture* Texture::LoadTexture(const String& path)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(*path, &width, &height, &nrChannels, 0);
		if (!data)
		{
			CY_ERROR("Failed to load texture from path: %s", *path);
			return nullptr;
		}

		Texture* texture = new Texture(width, height);

		glGenTextures(1, &texture->m_RendererId);
		glBindTexture(GL_TEXTURE_2D, texture->m_RendererId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		return texture;
	}
}
