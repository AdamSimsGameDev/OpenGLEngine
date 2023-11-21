#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"
#include "CyEngine/Components/Component.h"
#include "CyEngine/Editor/PropertyField.h"
#include "CyEngine/Objects/SceneObject.h"
#include "CyEngine/Scene.h"
#include "CyEngine/Serialization/Serialization.h"
#include "CyEngine/JSON/JSONUtility.h"

namespace Cy
{
	bool InspectorTab::RenderProperty(void* obj, const Class* objectClass, const String& prefix, const std::pair<String, ClassProperty>& prop)
	{
		return PropertyFieldBase::RenderPropertyOfType(obj, objectClass, prop);
	}

	void InspectorTab::RenderObject(void* obj, const Class* cl)
	{
		RenderObjectClass(obj, cl);
	}

	void InspectorTab::RenderObjectClass(void* obj, const Class* cl)
	{
		if (ImGui::TreeNode(cl->Name.c_str()))
		{
			for (const auto& pair : cl->Properties)
			{
				const bool hideInEditor = pair.second.GetMetaData("Hidden") != nullptr;
				if (hideInEditor)
					continue;

				if (RenderProperty(obj, cl, "", pair))
				{
					{
						const ClassPropertyMetaData* md = pair.second.GetMetaData("Tooltip");
						if (md && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(md->GetValue<std::string>().c_str());
						}
					}
					continue;
				}

				// see if the property itself is a class
				const Class* ncl = Class::GetClassFromName(pair.second.Type);
				if (ncl)
				{
					RenderObjectClass(cl->GetPropertyValuePtrFromName(pair.first, pair.second.Type, obj), ncl);
				}
			}

			SceneObject* so = cl->Name == "SceneObject" ? Cast<SceneObject>(obj) : nullptr;
			if (so)
			{
				for (const auto& comp : so->m_Components)
				{
					RenderObject(comp, comp->GetClass());
				}
			}

			if (ImGui::Button("Serialize"))
			{
				CY_CORE_LOG("JSON generated: {0}", JSONUtility::ConvertToJson(obj, cl));
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
				RenderObject(obj, obj->GetClass());
			}
		}

		ImGui::End();
	}
}
