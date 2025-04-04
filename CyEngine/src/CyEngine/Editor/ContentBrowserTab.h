#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Layers/EditorTab.h"
#include "CyEngine/Serialization/Directory.h"

namespace Cy
{
	class AssetInfo;
	class Texture;

	struct ContentBrowserButtonInfo
	{
		float Width;
		float Height;
		float Padding;

		ContentBrowserButtonInfo()
		{
			Width = 0.0f;
			Height = 0.0f;
			Padding = 0.0f;
		}

		ContentBrowserButtonInfo( float _Width, float _Height, float _Padding )
		{
			Width = _Width;
			Height = _Height;
			Padding = _Padding;
		}

		static ContentBrowserButtonInfo Lerp(const ContentBrowserButtonInfo& A, const ContentBrowserButtonInfo& B, float Alpha)
		{
			ContentBrowserButtonInfo N;
			N.Width = Math::Lerp( A.Width, B.Width, Alpha );
			N.Height = Math::Lerp( A.Height, B.Height, Alpha );
			N.Padding = Math::Lerp( A.Padding, B.Padding, Alpha );
			return N;
		}
	};

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

			MinButtonSize = { 80.0f, 90.0f, 10.0f };
			MaxButtonSize = { 160.0f, 180.0f, 20.0f };
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

	private:
		ContentBrowserButtonInfo MinButtonSize;
		ContentBrowserButtonInfo MaxButtonSize;
		ContentBrowserButtonInfo CurrentButtonSize;
		float ButtonSizeAlpha;
	};
}

