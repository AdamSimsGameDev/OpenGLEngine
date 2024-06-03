#pragma once

#include "CyEngine/Core.h"

namespace Cy
{
	class AssetInfo;

	class PathHelper
	{
	public:
		PathHelper(String inString);

		int Count() const { return m_PathElements.Count(); }

		String& operator[](int index)
		{
			return m_PathElements[index];
		}
		const String& operator[](int index) const
		{
			return m_PathElements[index];
		}

		String GetName() const { return m_Name; }
		String GetFileExtension() const { return m_FileExtension; }

		String RebuildPath() const;
		String RebuildRelativePath(const String& relativeTo) const;

		bool IsFile() const { return m_IsFile; }

	private:
		Array<String> m_PathElements;
		String m_FileExtension;
		String m_Name;
		bool m_IsFile;
	};

	class AssetManager
	{
	public:
		AssetManager()
			: m_Assets()
			, m_AssetTypes()
		{
		}

		static void Refresh();

		void RegisterAsset(AssetInfo* asset);
		void UnregisterAsset(AssetInfo* asset);

		static void SyncLoadAsset(int assetId);
		static void UnloadAsset(int assetId);

		static AssetInfo* GetAssetById(int assetId);
		template<typename AssetType>
		static AssetType* GetAssetById(int assetId)
		{
			AssetInfo* info = GetAssetById(assetId);
			if (AssetType* type = CastChecked<AssetType>(info))
			{
				return type;
			}
			return nullptr;
		}

		static bool ReadFromTextFile(const String& path, String& outString);
		static bool WriteToTextFile(const String& path, const String& inString);

		static AssetManager& Get();

	protected:
		virtual void Initialise();
		virtual void Refresh_Internal();

	private:
		Array<String> GatherAssetPaths() const;

	public:
		static String s_ProjectPath;
		static String s_AssetRelativePath;

	private:
		Array<AssetInfo*> m_Assets;
		Array<const AssetInfo*> m_AssetTypes;

		static int s_NextAssetId;
		static SharedPtr<AssetManager> s_AssetManager;
	};
}
