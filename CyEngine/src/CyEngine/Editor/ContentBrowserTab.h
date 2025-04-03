#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Layers/EditorTab.h"
#include "CyEngine/Serialization/Directory.h"

namespace Cy
{
	class AssetInfo;

	struct ContentBrowserFolder
	{
		String FolderName;
		Directory FullPath;

		Array<AssetInfo*> Assets;
		Array<ContentBrowserFolder, ArrayAllocatorLazy> Folders;

		ContentBrowserFolder()
		{
			FolderName = "";
			FullPath = Directory("");

			Assets = Array<AssetInfo*>();
			Folders = Array<ContentBrowserFolder, ArrayAllocatorLazy>();
		}

		bool FindFolder(const Directory& RelativePath, ContentBrowserFolder& OutFolder) const;
	};

	class ContentBrowserTab : public EditorTab
	{
	public:
		ContentBrowserTab()
			: EditorTab("Content Browser") 
		{
			Refresh();
			CurrentFolder = &RootFolder;
		}

		virtual void OnRender() override;

		bool FindFolder(const Directory& RelativePath, ContentBrowserFolder& OutFolder) const;

		void SetCurrentPath(const String& InPath);
		void Refresh();

	protected:
		void RenderAsset(AssetInfo* Asset);
		void RenderFolder(const ContentBrowserFolder& Folder);
		void RebuildRootFolder();
		void BuildFolderTree(ContentBrowserFolder& Folder, const Directory& Directory);

		ContentBrowserFolder RootFolder;

		String CurrentPath;
		ContentBrowserFolder* CurrentFolder;
	};
}

