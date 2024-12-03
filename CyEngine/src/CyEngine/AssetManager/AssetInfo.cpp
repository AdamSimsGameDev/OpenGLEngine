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

	void GetReferencesFrom(Object* Obj, Array<guid>& OutObjects)
	{
		// get our class
		const Class* MyClass = Obj->GetClass();

		// generate new references array from marked up Object properties
		Array<Object*> FoundObjects;
		for (auto Prop : MyClass->Properties)
		{
			// make sure we only check objects
			if (Prop.IsType<Object>())
			{
				// get the object
				Object* Found = MyClass->GetPropertyValueFromName<Object>(Prop.Name, Obj);
				if (Found == nullptr)
				{
					continue;
				}

				// check if the object is an asset itself
				if (AssetInfo* Asset = Found->GetParent<AssetInfo>())
				{
					OutObjects.Add(Asset->GetGUID());
				}
			}
		}
	}

	void AssetInfo::RebuildReferences()
	{
		// clear any existing references
		for (const auto& Reference : m_AssetsReferencing)
		{
			// get the asset
			if (AssetInfo* Info = AssetManager::GetAssetByGuid(Reference))
			{
				Info->m_AssetsReferencedBy.Remove(GetGUID());
			}
		}
		m_AssetsReferencing.Clear();

		// setup the references, internal references first
		Array<Object*> References = GetInternalObjectReferences();
	
		// loop over the existing references and work out what they reference
		// this only goes one layer deep but that should be fine?
		for (Object* Reference : References)
		{
			GetReferencesFrom(Reference, m_AssetsReferencing);
		}
	}
}
