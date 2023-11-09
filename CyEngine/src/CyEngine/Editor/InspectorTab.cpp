#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"
#include "CyEngine/Components/Component.h"
#include "CyEngine/Editor/PropertyField.h"
#include "CyEngine/Objects/SceneObject.h"
#include "CyEngine/Scene.h"
#include "CyEngine/Serialization/Serialization.h"

namespace Cy
{
	bool InspectorTab::RenderProperty(Object* obj, const String& prefix, const std::pair<String, ClassProperty>& prop)
	{
		return PropertyFieldBase::RenderPropertyOfType(obj, prefix + prop.first, prop);
	}

	void InspectorTab::RenderObject(Object* obj)
	{
		RenderObjectClass(obj, obj->GetClass());
	}

	void InspectorTab::RenderObjectClass(Object* obj, const Class* cl, String prefix)
	{
		if (ImGui::TreeNode(cl->Name.c_str()))
		{
			for (const auto& pair : cl->Properties)
			{
				if (RenderProperty(obj, prefix, pair))
				{
					const ClassPropertyMetaData* md = pair.second.GetMetaData("Tooltip");
					if (md && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
					{
						ImGui::SetTooltip(md->GetValue<std::string>().c_str());
					}
					continue;
				}

				// see if the property itself is a class
				const Class* ncl = Class::GetClassFromName(pair.second.Type);
				if (ncl)
				{
					RenderObjectClass(obj, ncl, prefix + pair.first + "|");
				}
			}

			if (cl == obj->GetClass())
			{
				if (SceneObject* so = Cast<SceneObject>(obj))
				{
					for (const auto& comp : so->m_Components)
					{
						RenderObject(comp);
					}
				}
			}

			if (ImGui::Button("Serialize"))
			{
				Serialization::SerializeObject(obj);
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
