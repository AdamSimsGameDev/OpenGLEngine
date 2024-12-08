#include "cypch.h"
#include "TextAsset.h"
#include "AssetManager.h"

namespace Cy
{
	bool TextAsset::OnSave()
	{
		if (!AssetManager::WriteToTextFile(m_FullPath, m_Content))
		{
			CY_ERROR("Failed to write text to file \"%s\" from path \"%s\". ", *GetName(), *m_Path);
			return false;
		}
		return true;
	}

	void TextAsset::OnLoad()
	{
		if (!AssetManager::ReadFromTextFile(m_FullPath, m_Content))
		{
			CY_ERROR("Failed to load text for file \"%s\" from path \"%s\". ", *GetName(), *m_Path);
		}

		CY_LOG("Loaded text from file {0}, test is:\n{1}", *GetName(), *m_Content);
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
