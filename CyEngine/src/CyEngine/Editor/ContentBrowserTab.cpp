#include "cypch.h"
#include <imgui.h>
#include "ContentBrowserTab.h"
#include "CyEngine/World.h"
#include "CyEngine/Textures/Texture.h"
#include "CyEngine/Serialization/File.h"

namespace Cy
{
	constexpr float ButtonSize = 75.0f;

	void ContentBrowserTab::OnRender()
	{
		ImGui::Begin("Content Browser", &m_TabOpen);

		if (CurrentFolder)
		{
			for (const auto& Folder : CurrentFolder->Folders)
			{
				RenderFolder(Folder);
			}

			for (const auto& Asset : CurrentFolder->Assets)
			{

			}
		}

		ImGui::End();
	}

	bool ContentBrowserTab::FindFolder(const Directory& RelativePath, ContentBrowserFolder& OutFolder) const
	{
		return RootFolder.FindFolder(RelativePath, OutFolder);
	}

	void ContentBrowserTab::SetCurrentPath(const String& InPath)
	{
		ContentBrowserFolder OutFolder;
		if (FindFolder(InPath, OutFolder))
		{
			CurrentPath = InPath;
			CurrentFolder = &OutFolder;
		}
	}

	void ContentBrowserTab::Refresh()
	{
		RebuildRootFolder();
	}

	void ContentBrowserTab::RenderAsset(AssetInfo* Asset)
	{

	}

	void ContentBrowserTab::RenderFolder(const ContentBrowserFolder& Folder)
	{
		ImGui::SetNextItemWidth(ButtonSize);
		ImGui::Button(*Folder.FolderName);
	}

	void ContentBrowserTab::RebuildRootFolder()
	{
		RootFolder = ContentBrowserFolder();
		BuildFolderTree(RootFolder, Directory::AssetsPath);
	}

	void ContentBrowserTab::BuildFolderTree(ContentBrowserFolder& Folder, const Directory& Directory)
	{
		Folder.FolderName = Directory.GetName();
		Folder.FullPath = Directory;

		const Array<String>& Folders = File::GetAllFoldersInDirectory(Directory, false);
		const Array<String>& Files = File::GetAllFilesInDirectory(Directory, false);

		// Get all of the folders
		for ( const auto& Subfolder : Folders )
		{
			ContentBrowserFolder NewFolder;
			BuildFolderTree(NewFolder, Subfolder);
			Folder.Folders.Add( NewFolder );
		}

		// Find all of the assets
	}

	bool ContentBrowserFolder::FindFolder(const Directory& RelativePath, ContentBrowserFolder& OutFolder) const
	{
		ContentBrowserFolder* Found = Folders.FindByPredicate([&](const ContentBrowserFolder& F) { return F.FolderName == RelativePath.First(); });
		if (!Found)
		{
			return false;
		}

		if (RelativePath.Length() == 1)
		{
			OutFolder = *Found;
			return true;
		}
		else
		{
			return Found->FindFolder(RelativePath.SubPath(), OutFolder);
		}
	}
}