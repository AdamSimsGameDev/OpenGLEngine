#include "cypch.h"
#include "AssetManager.h"

#include "AssetInfo.h"
#include "TextAsset.h"
#include "CyEngine/Serialization/File.h"

#include <filesystem>
#include <CyEngine/Serialization/Directory.h>

#include "CyEngine/ObjectManager.h"
#include "CyEngine/JSON/JSONUtility.h"

namespace Cy
{
	String AssetManager::s_ProjectPath = "";
	String AssetManager::s_AssetRelativePath = "/Assets";

	SharedPtr<AssetManager> AssetManager::s_AssetManager = nullptr;

	void AssetManager::Refresh()
	{
		Get().Refresh_Internal();
	}

	void AssetManager::RegisterAsset(AssetInfo* asset)
	{
		asset->OnRegister();
		m_Assets.Add(asset);
	}

	void AssetManager::UnregisterAsset(AssetInfo* asset)
	{
		m_Assets.Remove(asset);
		asset->OnUnregister();
	}

	void AssetManager::SyncLoadAsset(guid assetId)
	{
		AssetInfo* asset = GetAssetByGuid(assetId);
		SyncLoadAsset(asset);
	}

	void AssetManager::SyncLoadAsset(AssetInfo* asset)
	{
		if (asset && !asset->IsLoaded())
		{
			asset->m_IsLoaded = true;
			asset->m_IsLoading = false;
			asset->OnLoad();
		}
	}

	void AssetManager::UnloadAsset(guid assetId)
	{
		AssetInfo* asset = GetAssetByGuid(assetId);
		UnloadAsset(asset);
	}

	void AssetManager::UnloadAsset(AssetInfo* asset)
	{
		if (asset)
		{
			if (asset->IsLoaded())
			{
				asset->m_IsLoaded = false;
				asset->OnUnload();
			}
			else
			{
				asset->m_IsLoading = false;
			}
		}
	}

	void AssetManager::AsyncLoadAsset(guid assetId)
	{
		AssetInfo* asset = GetAssetByGuid(assetId);
		AsyncLoadAsset(asset);
	}

	void AssetManager::AsyncLoadAsset(AssetInfo* asset)
	{
		if (asset && !asset->IsLoaded() && !asset->IsLoading())
		{
			asset->SetIsLoading(true);
			Get().AssetAsyncLoadQueue.Enqueue(asset);
		}
	}

	AssetInfo* AssetManager::GetAssetByGuid(guid assetId)
	{
		for (auto a : Get().m_Assets)
		{
			if (a->GetGUID() == assetId)
			{
				return a;
			}
		}
		return nullptr;
	}

	Array<AssetInfo*> AssetManager::GetAllAssetsOfType(const Class* Type)
	{
		Array<AssetInfo*> arr;
		for (const auto& found : Get().m_Assets)
		{
			if (found->GetClass()->IsChildOf(Type))
			{
				arr.Add(found);
			}
		}
		return arr;
	}

	AssetMetaData AssetManager::FindOrCreateAssetMetaData(const String& AssetPath)
	{
		// Check to see if the meta file exists.
		const String MetaPath = AssetPath + ".meta";
		String OutData;
		if ( File::ReadFromTextFile(MetaPath, OutData) )
		{
			// Load the meta data from the Json
			AssetMetaData MetaData;
			JSONUtility::ConvertFromJson<AssetMetaData>( OutData, &MetaData );
			MetaData.guid = MetaData.guidStr;
			return MetaData;
		}
		else
		{
			AssetMetaData MetaData;
			MetaData.Name = AssetPath;
			MetaData.guid = guid::Make();
			MetaData.guidStr = MetaData.guid.Value;
			MetaData.DateLastModified = "TODO";

			File::WriteToTextFile( MetaPath, JSONUtility::ConvertToJson<AssetMetaData>( &MetaData ) );
			return MetaData;
		}
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
			Directory helper = Directory(path);

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

			if (type != nullptr)
			{
				Directory RelativeDir;
				helper.RelativeTo(Directory(s_ProjectPath + s_AssetRelativePath), RelativeDir);

				AssetMetaData MetaData = FindOrCreateAssetMetaData(helper.ToString());
				
				AssetInfo* asset = type->GetClass()->New<AssetInfo>();
				ObjectManager::Get()->RegisterObject(asset, MetaData.guid);
				asset->Initialise(helper.GetName(), helper.GetFileExtension(), RelativeDir.ToString(), helper.ToString());
				RegisterAsset(asset);

				// Test it with a sync load real quick
				AsyncLoadAsset(asset);
			}
		}
	}

	void AssetManager::LoadImmediate(AssetInfo* Info)
	{
		Info->m_IsLoaded = true;
		Info->OnLoad();
	}

	Array<String> AssetManager::GatherAssetPaths() const
	{
		Array<String> outPaths;

		const String& fullPath = s_ProjectPath + s_AssetRelativePath;
		for ( const String& Path : File::GetAllFilesInDirectory( fullPath, true ) )
		{
			const Array<String> Split = String::Split( Path, '.' );
			const String& Extension = Split.Last();
			const bool IsFile = Split.Count() > 1;
			if ( !IsFile )
			{
				continue;
			}

			// TODO: swap for a dictionary/map to make this less yucky!
			bool found = false;
			for ( int i = 0; i < m_AssetTypes.Count() && !found; i++ )
			{
				for ( auto ext : m_AssetTypes[ i ]->GetSupportedFileTypes() )
				{
					if ( ext == Extension )
					{
						found = true;
						break;
					}
				}
			}

			if ( found )
			{
				outPaths.Add( Path );
			}
		}

		return outPaths;
	}
}
