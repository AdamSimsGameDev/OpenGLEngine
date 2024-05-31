#include "cypch.h"
#include "TextAsset.h"
#include "AssetManager.h"

namespace Cy
{
	void TextAsset::OnLoad()
	{
		if (!AssetManager::ReadFromTextFile(m_FullPath, m_Content))
		{
			CY_ERROR("Failed to load text for file \"%s\" from path \"%s\". ", *m_Name, *m_Path);
		}
	}

	void TextAsset::OnUnload()
	{
		m_Content.Empty();
	}

	Array<String> TextAsset::GetSupportedFileTypes() const
	{
		return { ".txt" };
	}
}
