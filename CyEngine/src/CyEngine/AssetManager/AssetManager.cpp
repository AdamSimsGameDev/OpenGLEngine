#include "cypch.h"
#include "AssetManager.h"

#include "AssetInfo.h"
#include "TextAsset.h"

#include <sstream>
#include <filesystem>

namespace Cy
{
	PathHelper::PathHelper(String inString)
	{
		inString.ReplaceAll("\\", "/");		
		m_PathElements = String::Split(inString, '/');

		const String& ext = m_PathElements[m_PathElements.Count() - 1];
		Array<String> spl = String::Split(ext, '.');
		if (spl.Count() == 1)
		{
			m_IsFile = false;
			m_FileExtension = "";
		}
		else
		{
			m_IsFile = true;
			m_FileExtension = "." + spl.Pop();
		}

		m_Name = String::Combine(spl);
	}

	String PathHelper::RebuildPath() const
	{
		String newPath;
		for (int i = 0; i < Count(); i++)
		{
			if (i != 0)
			{
				newPath += "/";
			}

			newPath += m_PathElements[i];
		}
		return newPath;
	}

	String PathHelper::RebuildRelativePath(const String& relativeTo) const
	{
		const PathHelper& relativeToHelper = PathHelper(relativeTo);

		String newPath;
		for (int i = 0; i < Count(); i++)
		{
			if (i < relativeToHelper.Count() && relativeToHelper.m_PathElements[i] == m_PathElements[i])
			{
				continue;
			}

			if (!newPath.IsEmpty())
			{
				newPath += "/";
			}

			newPath += m_PathElements[i];
		}

		return newPath;
	}

	String AssetManager::s_ProjectPath = "";
	String AssetManager::s_AssetRelativePath = "/Assets";

	SharedPtr<AssetManager> AssetManager::s_AssetManager = nullptr;
	int AssetManager::s_NextAssetId = 0;

	void AssetManager::Refresh()
	{
		Get().Refresh_Internal();
	}

	void AssetManager::RegisterAsset(AssetInfo* asset)
	{
		asset->OnRegister(s_NextAssetId);
		s_NextAssetId++;
		m_Assets.Add(asset);
	}

	void AssetManager::UnregisterAsset(AssetInfo* asset)
	{
		m_Assets.Remove(asset);
		asset->OnUnregister();
	}

	void AssetManager::SyncLoadAsset(int assetId)
	{
		AssetInfo* asset = GetAssetById(assetId);
		if (asset && !asset->IsLoaded())
		{
			asset->m_IsLoaded = true;
			asset->OnLoad();
		}
	}

	void AssetManager::UnloadAsset(int assetId)
	{
		AssetInfo* asset = GetAssetById(assetId);
		if (asset && asset->IsLoaded())
		{
			asset->m_IsLoaded = false;
			asset->OnUnload();
		}
	}

	AssetInfo* AssetManager::GetAssetById(int assetId)
	{
		for (auto a : Get().m_Assets)
		{
			if (a->m_AssetId == assetId)
			{
				return a;
			}
		}
		return nullptr;
	}

	bool AssetManager::ReadFromTextFile(const String& path, String& outString)
	{
		std::ifstream infile;
		infile.open(path);

		if (infile.fail())
		{
			return false;
		}

		std::stringstream buffer;
		buffer << infile.rdbuf();

		outString = buffer.str();

		return true;
	}

	bool AssetManager::WriteToTextFile(const String& path, const String& inString)
	{
		return false;
	}

	AssetManager& AssetManager::Get()
	{
		if (s_AssetManager == nullptr)
		{
			s_AssetManager = new AssetManager();
			s_AssetManager->Initialise();
		}
		return *s_AssetManager;
	}

#define REGISTER_ASSET_TYPE(Asset) { const Asset##* asset = Asset##::GetStaticClass()->GetClassDefaultObject<Asset##>(); m_AssetTypes.Add(asset); }

	void AssetManager::Initialise()
	{
		s_ProjectPath = std::filesystem::current_path().generic_string();

		REGISTER_ASSET_TYPE(TextAsset);

		Refresh();
	}

	void AssetManager::Refresh_Internal()
	{
		const Array<String>& assetPaths = GatherAssetPaths();
		for (auto path : assetPaths)
		{
			PathHelper helper = PathHelper(path);

			// Get the asset type.
			// TODO: swap for a dictionary/map to make this less yucky!
			const AssetInfo* type = nullptr;
			for (int i = 0; i < m_AssetTypes.Count() && type == nullptr; i++)
			{
				for (auto ext : m_AssetTypes[i]->GetSupportedFileTypes())
				{
					if (ext == helper.GetFileExtension())
					{
						type = m_AssetTypes[i];
						break;
					}
				}
			}

			AssetInfo* asset = type->GetStaticClass()->New<AssetInfo>();
			asset->Initialise(helper.GetName(), helper.GetFileExtension(), helper.RebuildRelativePath(s_ProjectPath + s_AssetRelativePath), helper.RebuildPath());
			RegisterAsset(asset);
		}
	}

	Array<String> AssetManager::GatherAssetPaths() const
	{
		Array<String> outPaths;

		const String& fullPath = s_ProjectPath + s_AssetRelativePath;

		for (const auto& entry : std::filesystem::recursive_directory_iterator(*fullPath))
		{
			const String& fileExtension = entry.path().extension().string();
			const String& path = entry.path().string();

			// TODO: swap for a dictionary/map to make this less yucky!
			bool found = false;
			for (int i = 0; i < m_AssetTypes.Count() && !found; i++)
			{
				for (auto ext : m_AssetTypes[i]->GetSupportedFileTypes())
				{
					if (ext == fileExtension)
					{
						found = true;
						break;
					}
				}
			}

			if (found)
			{
				outPaths.Add(path);
			}
		}

		return outPaths;
	}
}
