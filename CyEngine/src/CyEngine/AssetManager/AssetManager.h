#pragma once

#include "CyEngine/Core.h"

namespace Cy
{
	class AssetInfo;

	class AssetManager
	{
		friend class AsyncLoadingThread;

	public:
		AssetManager()
			: m_Assets()
			, m_AssetTypes()
		{
		}

		static void Refresh();

		void RegisterAsset(AssetInfo* asset);
		void UnregisterAsset(AssetInfo* asset);

		static void SyncLoadAsset(guid assetId);
		static void SyncLoadAsset(AssetInfo* asset);

		static void UnloadAsset(guid assetId);
		static void UnloadAsset(AssetInfo* asset);

		static void AsyncLoadAsset(guid assetId);
		static void AsyncLoadAsset(AssetInfo* asset);

		static AssetInfo* GetAssetByGuid(guid assetId);
		template<typename AssetType>
		static AssetType* GetAssetByGuid(guid assetId)
		{
			AssetInfo* info = GetAssetByGuid(assetId);
			if (AssetType* type = CastChecked<AssetType>(info))
			{
				return type;
			}
			return nullptr;
		}

		template<typename T>
		static Array<T*> GetAllAssetsOfType()
		{
			return GetAllAssetsOfType(T::StaticClass());
		}

		static Array<AssetInfo*> GetAllAssetsOfType(const Class* Type);

		static AssetManager& Get();

	protected:
		virtual void Initialise();
		virtual void Refresh_Internal();

		void LoadImmediate(AssetInfo* Info);

	private:
		Array<String> GatherAssetPaths() const;

	public:
		static String s_ProjectPath;
		static String s_AssetRelativePath;

	private:
		// TODO: Swap this out for a HashSet when I eventually make one
		Array<AssetInfo*> m_Assets;
		Array<const AssetInfo*> m_AssetTypes;

		Queue<AssetInfo*> AssetAsyncLoadQueue;

		static SharedPtr<AssetManager> s_AssetManager;
	};
}
