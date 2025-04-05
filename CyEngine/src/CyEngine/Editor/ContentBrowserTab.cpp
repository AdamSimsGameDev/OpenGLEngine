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
	void ContentBrowserTab::OnRender()
	{
		ImGui::Begin("Content Browser", &m_TabOpen);

		CurrentButtonSize = ContentBrowserButtonInfo::Lerp( MinButtonSize, MaxButtonSize, ButtonSizeAlpha );

		if (CurrentFolder)
		{
			const float ButtonSpacing = CurrentButtonSize.Padding;
			const float ButtonWidth = CurrentButtonSize.Width;
			const float ButtonHeight = CurrentButtonSize.Height;

			const int MaxHorizontal = (int)floor(ImGui::GetContentRegionAvail().x - ButtonSpacing) / (ButtonSpacing + ButtonWidth);

			int X = 0;
			int Y = 0;

			if (CurrentFolder->Parent != nullptr)
			{
				ImGui::SetCursorPos(ImVec2(
					ImGui::GetWindowContentRegionMin().x + ButtonSpacing + (X * (ButtonSpacing + ButtonWidth)),
					ImGui::GetWindowContentRegionMin().y + ButtonSpacing + (Y * (ButtonSpacing + ButtonHeight)))
					);
				bool IsDoubleClicked = false;
				bool IsSelected = CurrentFolder->Parent->FullPath.ToString() == SelectedElement && World::Get()->CurrentSelectedObject != nullptr;
				RenderSelectable("../", CurrentFolder->Parent->FullPath.ToString(), FolderTextureOpen, IsSelected, IsDoubleClicked);
				if (IsSelected)
				{
					World::Get()->CurrentSelectedObject.Clear();
				}
				
				if (IsDoubleClicked)
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

			if ( !SelectedElement.IsEmpty() )
			{
				// Selected element inputs go here
				if ( Input::IsKeyReleased( CY_KEY_ENTER ) )
				{
					SetCurrentPath( SelectedElement );
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

	bool ContentBrowserTab::FindFolder(const Directory& Path, ContentBrowserFolder*& OutFolder) const
	{
		Directory RelativePath;
		if ( Path.RelativeTo( RootFolder.FullPath, RelativePath ) )
		{
			CY_LOG( "Relative path is {0}", *RelativePath.ToString() );
			return RootFolder.FindFolder( RelativePath, OutFolder );
		}
		return false;
	}

	void ContentBrowserTab::SetCurrentPath(const String& InPath)
	{
		if (InPath == RootFolder.FullPath.ToString())
		{
			CurrentPath = InPath;
			CurrentFolder = &RootFolder;
			return;
		}
		
		ContentBrowserFolder* OutFolder;
		if (FindFolder(InPath, OutFolder))
		{
			CurrentPath = InPath;
			CurrentFolder = OutFolder;
		}
	}

	void ContentBrowserTab::Refresh()
	{
		RebuildRootFolder();
	}

	void ContentBrowserTab::RenderAsset(AssetInfo* Asset)
	{
		String Name = Asset->GetName();
		if (Asset->IsDirty())
		{
			Name += " *";
		}
		
		bool IsDoubleClicked = false;
		bool IsSelected = Asset->GetFullPath() == SelectedElement && World::Get()->CurrentSelectedObject == Asset;
		RenderSelectable(Name, Asset->GetFullPath(), DocumentTexture, IsSelected, IsDoubleClicked);
		
		if (IsSelected)
		{
			SharedPtr<Object> Shared = ObjectManager::GetSharedObjectPtr(Asset);
			World::Get()->CurrentSelectedObject = Shared.MakeWeak();

			if (Input::IsKeyDown(CY_KEY_LEFT_CONTROL) && Input::IsKeyReleased(CY_KEY_S))
			{
				Asset->Save();
			}
		}
	}

	void ContentBrowserTab::RenderFolder(const ContentBrowserFolder& Folder)
	{
		bool IsDoubleClicked = false;
		bool IsSelected = Folder.FullPath.ToString() == SelectedElement && World::Get()->CurrentSelectedObject == nullptr;
		RenderSelectable(Folder.FolderName, Folder.FullPath.ToString(), FolderTexture, IsSelected, IsDoubleClicked);

		if (IsSelected)
		{
			World::Get()->CurrentSelectedObject.Clear();
		}
		
		if (IsDoubleClicked)
		{
			CurrentFolder = &Folder;
		}
	}

	void ContentBrowserTab::RenderSelectable(String Title, String Path, Texture* Icon, bool& IsSelected, bool& IsDoubleClicked)
	{
		ImVec2 StartPos = ImGui::GetCursorPos();

		const bool Selected = ImGui::Selectable(*String::Format("##%sContentBrowserButton", *Title), IsSelected, ImGuiSelectableFlags_AllowDoubleClick, ImVec2( CurrentButtonSize.Width, CurrentButtonSize.Height));
		if (Selected)
		{
			SelectedElement = Path;
			IsSelected = true;
		}

		// Double click to open
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::GetMouseClickedCount( ImGuiMouseButton_Left ) >= 2)
		{
			IsDoubleClicked = true;
			return;
		}

		// Text field
		float TextWidth = ImGui::CalcTextSize(*Title).x;
		const float HalfWidth = CurrentButtonSize.Width / 2.0f;
		ImGui::SetCursorPos(ImVec2(StartPos.x + (HalfWidth - TextWidth * 0.5f), StartPos.y + CurrentButtonSize.Height - 30.0f));
		ImGui::Text("%s", *Title);

		// Image
		ImGui::SetCursorPos(ImVec2(StartPos.x + 10.0f, StartPos.y + 10.0f));
		ImGui::Image(reinterpret_cast<ImTextureID>(Icon->m_RendererId), ImVec2(140.0f, 140.0f));
		
		// TODO: Add input field to change the assets name
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

	bool ContentBrowserFolder::FindFolder(const Directory& RelativePath, ContentBrowserFolder*& OutFolder) const
	{
		ContentBrowserFolder* Found = Folders.FindByPredicate([&](const ContentBrowserFolder& F) { return F.FolderName == RelativePath.First(); });
		if (!Found)
		{
			return false;
		}

		if (RelativePath.Length() == 1)
		{
			OutFolder = Found;
			return true;
		}
		else
		{
			return Found->FindFolder(RelativePath.SubPath(), OutFolder);
		}
	}
}