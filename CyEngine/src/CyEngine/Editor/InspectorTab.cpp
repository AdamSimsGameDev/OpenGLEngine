#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"
#include "CyEngine/Renderer/Camera.h"

namespace Cy
{
	void InspectorTab::OnRender()
	{
		ImGui::Begin("Inspector", &m_TabOpen);

		Scene* scene = Scene::Get();
		if (scene)
		{
			if (Camera* camera = Application::Get().GetCamera())
			{
				if (ImGui::TreeNode("Camera"))
				{
					if (ImGui::TreeNode("Transform"))
					{
						const Transform& transform = camera->GetTransform();
						ImGui::Text((std::string("Position: ") + transform.GetPosition().ToString()).data());
						ImGui::Text((std::string("Rotation: ") + transform.GetRotation().ToString()).data());
						ImGui::Text((std::string("Scale: ") + transform.GetScale().ToString()).data());
						ImGui::Text((std::string("Proj: ") + camera->GetProjectionViewMatrix().ToString()).data());
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
			}

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
