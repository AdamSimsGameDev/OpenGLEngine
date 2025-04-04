#include "cypch.h"
#include <imgui.h>
#include "ContentBrowserTab.h"
#include "CyEngine/World.h"
#include "CyEngine/AssetManager/AssetInfo.h"
#include "CyEngine/AssetManager/AssetManager.h"
#include "CyEngine/Textures/Texture.h"
#include "CyEngine/Serialization/File.h"

namespace Cy
{
	constexpr float ButtonWidth = 160.0f;
	constexpr float ButtonHeight = 180.0f;
	constexpr float ButtonSpacing = 20.0f;

	void ContentBrowserTab::OnRender()
	{
		ImGui::Begin("Content Browser", &m_TabOpen);

		if (CurrentFolder)
		{
			const int MaxHorizontal = (int)floor(ImGui::GetContentRegionAvail().x - ButtonSpacing) / (ButtonSpacing + ButtonWidth);

			int X = 0;
			int Y = 0;

			if (CurrentFolder->Parent != nullptr)
			{
				ImGui::SetCursorPos(ImVec2(
					ImGui::GetWindowContentRegionMin().x + ButtonSpacing + (X * (ButtonSpacing + ButtonWidth)),
					ImGui::GetWindowContentRegionMin().y + ButtonSpacing + (Y * (ButtonSpacing + ButtonHeight)))
					);
				if (RenderSelectable("../", CurrentFolder->Parent->FullPath.ToString(), FolderTextureOpen))
				{
					CurrentFolder = CurrentFolder->Parent;
					ImGui::End();
					return;
				}
				
				X++;
				if (X == MaxHorizontal)
				{
					X = 0;
					Y++;
				}
			}

			for (const auto& Folder : CurrentFolder->Folders)
			{
				ImGui::SetCursorPos(ImVec2(
					ImGui::GetWindowContentRegionMin().x + ButtonSpacing + (X * (ButtonSpacing + ButtonWidth)),
					ImGui::GetWindowContentRegionMin().y + ButtonSpacing + (Y * (ButtonSpacing + ButtonHeight)))
					);
				RenderFolder(Folder);
				
				X++;
				if (X == MaxHorizontal)
				{
					X = 0;
					Y++;
				}
			}

			for (const auto& Asset : CurrentFolder->Assets)
			{
				ImGui::SetCursorPos(ImVec2(
					ImGui::GetWindowContentRegionMin().x + ButtonSpacing + (X * (ButtonSpacing + ButtonWidth)),
					ImGui::GetWindowContentRegionMin().y + ButtonSpacing + (Y * (ButtonSpacing + ButtonHeight)))
					);
				RenderAsset(Asset);

				X++;
				if (X == MaxHorizontal)
				{
					X = 0;
					Y++;
				}
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
		if (RenderSelectable(Asset->GetName(), Asset->GetFullPath(), DocumentTexture))
		{
			// TODO: Open things?
		}
	}

	void ContentBrowserTab::RenderFolder(const ContentBrowserFolder& Folder)
	{
		if (RenderSelectable(Folder.FolderName, Folder.FullPath.ToString(), FolderTexture))
		{
			CurrentFolder = &Folder;
		}
	}

	bool ContentBrowserTab::RenderSelectable(String Title, String Path, Texture* Icon)
	{
		ImVec2 StartPos = ImGui::GetCursorPos();

		const bool IsSelected = ImGui::Selectable(*String::Format("##%sContentBrowserButton", *Title), SelectedElement == Path, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ButtonWidth, ButtonHeight));
		if (IsSelected)
		{
			SelectedElement = Path;
		}

		// Double click to open
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			return true;
		}

		// Text field
		float TextWidth = ImGui::CalcTextSize(*Title).x;
		constexpr float HalfWidth = ButtonWidth / 2.0f;
		ImGui::SetCursorPos(ImVec2(StartPos.x + (HalfWidth - TextWidth * 0.5f), StartPos.y + ButtonHeight - 30.0f));
		ImGui::Text("%s", *Title);

		// Image
		ImGui::SetCursorPos(ImVec2(StartPos.x + 10.0f, StartPos.y + 10.0f));
		ImGui::Image(reinterpret_cast<ImTextureID>(Icon->m_RendererId), ImVec2(140.0f, 140.0f));
		
		// TODO: Add input field to change the assets name

		return false;
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
			NewFolder.Parent = &Folder;
			BuildFolderTree(NewFolder, Subfolder);
			Folder.Folders.Add( NewFolder );
		}

		// Find all of the assets
		for (const auto& File : Files)
		{
			if (auto* Found = AssetManager::FindAssetByPath(File))
			{
				Folder.Assets.Add(Found);
			}
		}
	}

	void ContentBrowserTab::LoadAssets()
	{
		FolderTexture = Texture::LoadTexture("resources/icon_folder.png");
		FolderTextureOpen = Texture::LoadTexture("resources/icon_folder_open.png");
		DocumentTexture = Texture::LoadTexture("resources/icon_document.png");
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