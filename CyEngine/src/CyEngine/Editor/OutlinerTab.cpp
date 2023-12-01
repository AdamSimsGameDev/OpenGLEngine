#include "cypch.h"
#include <imgui.h>
#include "OutlinerTab.h"
#include "CyEngine/Scene.h"

namespace Cy
{
	void OutlinerTab::OnRender()
	{
		ImGui::Begin("Outliner", &m_TabOpen);

		// generate the items list
		Array<const char*> arr;
		Scene* scene = Scene::Get();
		if (scene)
		{
			int current_item = -1;
			for (SceneObject* so : scene->GetSceneObjects())
			{
				if (scene->CurrentSelectedObject == so)
				{
					current_item = arr.Count();
				}
				arr.Add(*so->Name);
			}

			int height_in_items;
			float item_height = ImGui::GetTextLineHeightWithSpacing();
			float available_height = ImGui::GetContentRegionMax().y - (ImGui::GetStyle().FramePadding.y * 2.0f);
			int available_count = floor(available_height / item_height) - 2;

			ImGui::SetNextItemWidth(-1);
			if (ImGui::ListBox("##Outliner", &current_item, *arr, arr.Count(), available_count))
			{
				scene->CurrentSelectedObject = scene->GetSceneObjects()[current_item];
			}
		}

		ImGui::End();
	}
}