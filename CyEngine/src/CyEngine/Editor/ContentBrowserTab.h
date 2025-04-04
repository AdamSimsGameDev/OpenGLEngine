#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Layers/EditorTab.h"
#include "CyEngine/Serialization/Directory.h"

namespace Cy
{
	class AssetInfo;
	class Texture;

	struct ContentBrowserFolder
	{
		String FolderName;
		Directory FullPath;

		ContentBrowserFolder* Parent;
		
		Array<AssetInfo*> Assets;
		Array<ContentBrowserFolder, ArrayAllocatorLazy> Folders;

		ContentBrowserFolder()
		{
			FolderName = "";
			FullPath = Directory("");
			Parent = nullptr;
			
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
			, RootFolder()
		{
			LoadAssets();
			Refresh();

			CurrentFolder = &RootFolder;
			SelectedElement = "";
		}

		virtual void OnRender() override;

		bool FindFolder(const Directory& RelativePath, ContentBrowserFolder& OutFolder) const;

		void SetCurrentPath(const String& InPath);
		void Refresh();

	protected:
		void RenderAsset(AssetInfo* Asset);
		void RenderFolder(const ContentBrowserFolder& Folder);

		bool RenderSelectable(String Title, String Path, Texture* Icon);
		
		void RebuildRootFolder();
		void BuildFolderTree(ContentBrowserFolder& Folder, const Directory& Directory);

		void LoadAssets();
		
		ContentBrowserFolder RootFolder;

		String SelectedElement;
		String CurrentPath;
		const ContentBrowserFolder* CurrentFolder;

		Texture* FolderTexture;
		Texture* FolderTextureOpen;
		Texture* DocumentTexture;
	};
}

