#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"

namespace Cy
{
	void InspectorTab::RenderObject(Object* obj)
	{
		const Class* cl = obj->GetClass();
		if (ImGui::TreeNode(cl->Name.c_str()))
		{
			for (const auto& pair : cl->Properties)
			{
				if (Transform* t = cl->GetPropertyValueFromName<Object, Transform>(pair.first, obj))
				{
					// POSITION
					float pos[3]{ t->Position.x, t->Position.y, t->Position.z };
					ImGui::DragFloat3("Position", pos);
					t->SetPosition({ pos[0], pos[1], pos[2] });

					// ROTATION
					Vector3 v = Quat::ToEuler(t->Rotation);
					float rot[3]{ v.x, v.y, v.z };
					ImGui::DragFloat3("Rotation", rot);
					t->SetRotation(Quat::FromEuler({ rot[0], rot[1], rot[2] }));

					// SCALE
					float scl[3]{ t->Scale.x, t->Scale.y, t->Scale.z };
					ImGui::DragFloat3("Scale", scl);
					t->SetScale({ scl[0], scl[1], scl[2] });
				}
				else if (int* i = cl->GetPropertyValueFromName<Object, int>(pair.first, obj))
				{
					ImGui::DragInt(pair.first.c_str(), i);
				}
				else if (float* i = cl->GetPropertyValueFromName<Object, float>(pair.first, obj))
				{
					ImGui::DragFloat(pair.first.c_str(), i);
				}
				else if (bool* i = cl->GetPropertyValueFromName<Object, bool>(pair.first, obj))
				{
					ImGui::Checkbox(pair.first.c_str(), i);
				}
			}

			if (SceneObject* so = Cast<SceneObject>(obj))
			{
				for (const auto& comp : so->m_Components)
				{
					RenderObject(comp);
				}
			}

			ImGui::TreePop();
		}
	}

	void InspectorTab::OnRender()
	{
		ImGui::Begin("Inspector", &m_TabOpen);

		Scene* scene = Scene::Get();
		if (scene)
		{
			for (SceneObject* obj : scene->GetSceneObjects())
			{
				RenderObject(obj);
			}
		}

		ImGui::End();
	}
}
