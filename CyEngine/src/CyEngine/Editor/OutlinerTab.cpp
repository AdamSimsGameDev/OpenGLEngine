#include "cypch.h"
#include <imgui.h>
#include "OutlinerTab.h"
#include "CyEngine/World.h"

namespace Cy
{
	void RenderTree(const Array<SceneObject*>& objects, SceneObject*& currentItem, bool isRoot = false)
	{
		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_DefaultOpen;

		for (int i = 0; i < objects.Count(); i++)
		{
			if (!objects[i] || (isRoot && objects[i]->GetParent<SceneObject>()))
			{
				continue;
			}

			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool is_selected = currentItem == objects[i];
			if (is_selected)
				node_flags |= ImGuiTreeNodeFlags_Selected;
			if (objects[i]->GetChildCount() == 0)
				node_flags |= ImGuiTreeNodeFlags_Leaf;
			if (i < 3)
			{
				bool node_open = ImGui::TreeNodeEx(*(objects[i]->GetGUID().Value), node_flags, *String::Format("%s", objects[i]->Name));
				if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
					currentItem = objects[i];
				if (ImGui::BeginDragDropSource())
				{
					ImGui::SetDragDropPayload("_OUTLINER", &objects[i], sizeof(SceneObject*));
					ImGui::EndDragDropSource();
				}
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_OUTLINER"))
					{
						SceneObject* target = *(SceneObject**)payload->Data;
						if (target != objects[i])
							target->SetParent(objects[i]);
					}
					ImGui::EndDragDropTarget();
				}
				if (node_open)
				{
					RenderTree(objects[i]->GetChildren(), currentItem);
					ImGui::TreePop();
				}
			}
		}
	}

	void OutlinerTab::OnRender()
	{
		ImGui::Begin("Outliner", &m_TabOpen);

		World* scene = World::Get();
		if (scene)
		{
			if (ImGui::Button("+##NewObject"))
			{
				SceneObject* so = scene->CreateSceneObject<SceneObject>(Vector3::Zero, Quat::Identity);
				so->Name = "New Object";
			}

			SceneObject* currentItem = scene->CurrentSelectedObject;
			if (ImGui::TreeNodeEx("World##Outliner", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_OUTLINER"))
					{
						SceneObject* target = *(SceneObject**)payload->Data;
						target->SetParent(nullptr);
					}
					ImGui::EndDragDropTarget();
				}

				const Array<SceneObject*> objects = scene->GetSceneObjects();
				RenderTree(objects, currentItem, true);

				if (currentItem != scene->CurrentSelectedObject)
				{
					scene->CurrentSelectedObject = ObjectManager::GetSharedPtrTyped<SceneObject>(currentItem).MakeWeak();
				}

				ImGui::TreePop();
			}
		}

		ImGui::End();
	}
}