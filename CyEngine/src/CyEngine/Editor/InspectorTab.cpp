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

	void SetClipboardText(std::string text)
	{
		const size_t len = text.length() + 1;

		HGLOBAL hgl = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hgl), text.c_str(), len);
		GlobalUnlock(hgl);

		OpenClipboard(NULL);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hgl);
		CloseClipboard();
	}

	std::string GetClipboardText()
	{
		OpenClipboard(nullptr);
		HANDLE hData = GetClipboardData(CF_TEXT);

		char* pszText = static_cast<char*>(GlobalLock(hData));
		std::string text(pszText);

		GlobalUnlock(hData);
		CloseClipboard();

		return text;
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

			if (ImGui::Button("Copy to Clipboard"))
			{
				std::string json = JSONUtility::ConvertToJson(obj, cl);
				CY_CORE_LOG("JSON generated:\n{0}", json);
				SetClipboardText(json);
			}
			if (ImGui::Button("Paste from Clipboard"))
			{
				JSONUtility::ConvertFromJson(GetClipboardText(), obj, cl);
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
