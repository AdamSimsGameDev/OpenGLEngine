#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "generated/AssetInfo.gen.h"

namespace Cy
{
	CLASS(Abstract)
	class AssetInfo : public Object
	{
		GENERATED_CLASS(AssetInfo)

		friend class AssetManager;

	public:
		void Initialise(String name, String fileType, String path, String fullPath)
		{
			m_Name = name;
			m_FileType = fileType;
			m_Path = path;
			m_FullPath = fullPath;

			m_IsLoaded = false;
			m_AssetId = -1;
		}

		virtual void OnRegister(int assetId);
		virtual void OnUnregister();

		const String& GetPath() const { return m_Path; }
		const String& GetFullPath() const { return m_FullPath; }

		bool IsRegistered() const { return m_AssetId >= 0; }
		bool IsLoaded() const { return m_IsLoaded; }

		void SyncLoad();
		void Unload();

		bool Save();

		void MarkDirty() { m_IsDirty = true; }
		bool IsDirty() const { return m_IsDirty; }

		void SetIsLoading(bool isLoading) { m_IsLoading = isLoading; }
		bool IsLoading() const { return m_IsLoading; }

	protected:
		virtual bool OnSave() = 0;

		virtual void OnLoad() = 0;
		virtual void OnUnload() = 0;

		virtual Array<String> GetSupportedFileTypes() const = 0;

	protected:
		String m_Name;
		String m_FileType;

		String m_Path;
		String m_FullPath;

		std::atomic<bool> m_IsLoading;

		bool m_IsLoaded;
		int m_AssetId;

		bool m_IsDirty;
	};
}
