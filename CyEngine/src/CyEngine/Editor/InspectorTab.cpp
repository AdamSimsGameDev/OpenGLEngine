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

	void SetClipboardText(String text)
	{
		const size_t len = text.Length() + 1;

		HGLOBAL hgl = GlobalAlloc(GMEM_MOVEABLE, len);
		memcpy(GlobalLock(hgl), *text, len);
		GlobalUnlock(hgl);

		OpenClipboard(NULL);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hgl);
		CloseClipboard();
	}

	String GetClipboardText()
	{
		OpenClipboard(nullptr);
		HANDLE hData = GetClipboardData(CF_TEXT);

		char* pszText = static_cast<char*>(GlobalLock(hData));
		String text(pszText);

		GlobalUnlock(hData);
		CloseClipboard();

		return text;
	}

	void InspectorTab::RenderObjectClass(void* obj, const Class* cl)
	{
		if (ImGui::TreeNode(*cl->Name))
		{
			for (const auto& pair : cl->Properties)
			{
				const bool hideInEditor = pair.second.GetMetaData("Hidden") != nullptr;
				if (hideInEditor)
					continue;

				// if we are an array we need to do something slightly different.
				if (pair.second.IsArray)
				{
					size_t s = cl->GetArraySizeFromName(pair.first, pair.second.Type, obj);
					// draw the array header, and then the individual sub-properties.
					if (ImGui::TreeNode(*pair.first, *String::Format("%s [%i]", *pair.first, s)))
					{
						ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 7.5f);
						if (ImGui::Button("+", ImVec2(16.0f, ImGui::GetFrameHeight())))
						{
							ArrayBase* arr = reinterpret_cast<ArrayBase*>(cl->GetPropertyValuePtrFromName(pair.first, pair.second.Type, obj));
							arr->AddDefault();
						}
						Array<size_t> toRemove;
						for (size_t i = 0; i < s; i++)
						{
							std::pair<Cy::String, Cy::ClassProperty> n = pair;
							n.first = n.first + "." + Cy::String::ToString((int)i);
							if (RenderProperty(obj, cl, "", n))
							{
								ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 7.5f);
								if (ImGui::Button(*String::Format("-##%i", i), ImVec2(16.0f, ImGui::GetFrameHeight())))
								{
									toRemove.Add(i);
								}
								continue;
							}
						}
						for (size_t t : toRemove)
						{
							ArrayBase* arr = reinterpret_cast<ArrayBase*>(cl->GetPropertyValuePtrFromName(pair.first, pair.second.Type, obj));
							arr->RemoveAt(t);
						}
						ImGui::TreePop();
					}
					continue;
				}

				if (RenderProperty(obj, cl, "", pair))
				{
					{
						const ClassPropertyMetaData* md = pair.second.GetMetaData("Tooltip");
						if (md && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
						{
							ImGui::SetTooltip(*md->GetValue<String>());
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

			//if (ImGui::Button("Copy to Clipboard"))
			//{
			//	String json = JSONUtility::ConvertToJson(obj, cl);
			//	CY_CORE_LOG("JSON generated:\n{0}", *json);
			//	SetClipboardText(json);
			//}
			//if (ImGui::Button("Paste from Clipboard"))
			//{
			//	JSONUtility::ConvertFromJson(GetClipboardText(), obj, cl);
			//}

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
