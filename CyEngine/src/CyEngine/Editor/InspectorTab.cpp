#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"

namespace Cy
{
	void InspectorTab::OnRender()
	{
		ImGui::Begin("Inspector", &m_TabOpen);

		Scene* scene = Scene::Get();
		if (scene)
		{
			for (const SceneObject* obj : scene->GetSceneObjects())
			{
				if (ImGui::TreeNode(obj->ClassName().data()))
				{
					if (ImGui::TreeNode("Transform")) 
					{
						const Transform& transform = obj->GetTransform();
						ImGui::Text((std::string("Position: ") + transform.GetPosition().ToString()).data());
						ImGui::Text((std::string("Rotation: ") + transform.GetRotation().ToString()).data());
						ImGui::Text((std::string("Scale: ") + transform.GetScale().ToString()).data());
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
			}
		}

		ImGui::End();
	}
}
