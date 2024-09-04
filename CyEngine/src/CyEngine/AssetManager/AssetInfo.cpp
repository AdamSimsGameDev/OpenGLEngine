#include "cypch.h"
#include "AssetInfo.h"
#include "CyEngine/AssetManager/AssetManager.h"

namespace Cy
{
	void AssetInfo::OnRegister(int assetId)
	{
		m_AssetId = assetId;
	}

	void AssetInfo::OnUnregister()
	{
		m_AssetId = -1;
	}

	void AssetInfo::SyncLoad()
	{
		AssetManager::Get().SyncLoadAsset(GetGUID());
	}

	void AssetInfo::Unload()
	{
		AssetManager::Get().UnloadAsset(GetGUID());
	}

	bool AssetInfo::Save()
	{
		if (OnSave())
		{
			m_IsDirty = false;
			return true;
		}
		return false;
	}
}
