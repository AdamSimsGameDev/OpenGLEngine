#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"
#include "CyEngine/Components/Component.h"
#include "CyEngine/Editor/PropertyField.h"
#include "CyEngine/Objects/SceneObject.h"
#include "CyEngine/World.h"
#include "CyEngine/Serialization/Serialization.h"
#include "CyEngine/JSON/JSONUtility.h"

namespace Cy
{
	bool InspectorTab::RenderProperty(void* obj, const Class* objectClass, const String& prefix, const std::pair<String, ClassProperty>& prop)
	{
		// if we are an enum render differently.
		if (prop.second.IsEnum)
		{
			static const String ENUM_NAME = "Enum";
			PropertyFieldBase::RenderPropertyOfType(obj, objectClass, prop, &ENUM_NAME);
			return true;
		}

		if (PropertyFieldBase::RenderPropertyOfType(obj, objectClass, prop))
		{
			{
				const MetaDataProperty* md = prop.second.GetMetaData("Tooltip");
				if (md && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				{
					ImGui::SetTooltip(*md->GetValue<String>());
				}
			}
			return true;
		}

		// see if the property itself is a class
		const Class* ncl = Class::GetClassFromName(prop.second.Type);
		if (ncl)
		{
			RenderObjectClass(objectClass->GetPropertyValuePtrFromName(prop.first, prop.second.Type, obj), ncl, true);
			return true;
		}

		return false;
	}

	void InspectorTab::RenderObject(void* obj, const Class* cl, bool showHeader)
	{
		RenderObjectClass(obj, cl, showHeader);
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

	void InspectorTab::RenderObjectClass(void* obj, const Class* cl, bool showHeader)
	{
		if (!showHeader || ImGui::CollapsingHeader(*cl->Name, ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (showHeader && ImGui::IsItemHovered())
			{
				if (Component* component = reinterpret_cast<Component*>(obj))
				{
					if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
					{
						ImGui::OpenPopup(*String::Format("rightclickcontext_%s", *component->GetGUID().Value));
					}
				}
			}

			for (const auto& pair : cl->Properties)
			{
				const bool hideInEditor = pair.second.GetMetaData("Hidden") != nullptr;
				if (hideInEditor)
					continue;

				// if we are an array we need to do something slightly different.
				if (pair.second.IsArray)
				{
					int s = cl->GetArraySizeFromName(pair.first, pair.second.Type, obj);
					// draw the array header, and then the individual sub-properties.
					if (ImGui::TreeNode(*pair.first, *String::Format("%s [%i]", *pair.first, s)))
					{
						ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 7.5f);
						if (ImGui::Button("+", ImVec2(16.0f, ImGui::GetFrameHeight())))
						{
							ArrayBase* arr = reinterpret_cast<ArrayBase*>(cl->GetPropertyValuePtrFromName(pair.first, pair.second.Type, obj));
							arr->AddDefault();
						}
						Array<int> toRemove;
						for (int i = 0; i < s; i++)
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
						for (int t : toRemove)
						{
							ArrayBase* arr = reinterpret_cast<ArrayBase*>(cl->GetPropertyValuePtrFromName(pair.first, pair.second.Type, obj));
							arr->RemoveAt(t);
						}
						ImGui::TreePop();
					}
					continue;
				}

				RenderProperty(obj, cl, "", pair);
			}

			if (cl->Name == "SceneObject")
			{
				if (SceneObject* so = reinterpret_cast<SceneObject*>(obj))
				{
					for (const auto& comp : so->GetComponents())
					{
						RenderObject(comp, comp->GetClass(), true);
					}
				}
			}
		}

		if (Component* component = reinterpret_cast<Component*>(obj))
		{
			if (ImGui::BeginPopup(*String::Format("rightclickcontext_%s", *component->GetGUID().Value)))
			{
				if (ImGui::MenuItem("Remove Component"))
				{
					component->GetOwner()->RemoveComponent(component);
					component->Destroy();
				}

				ImGui::EndPopup();
			}
		}
	}

	void InspectorTab::OnRender()
	{
		ImGui::Begin("Inspector", &m_TabOpen);

		World* scene = World::Get();
		if (scene && scene->CurrentSelectedObject)
		{
			RenderObject(scene->CurrentSelectedObject, scene->CurrentSelectedObject->GetClass(), false);
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, 30.0f)))
			{
				ImGui::OpenPopup("##AddComponent");
			}

			if (ImGui::BeginPopup("##AddComponent"))
			{
				Array<const Class*> classes = Class::GetChildClassesOfType<Component>();
				for (const auto& cl : classes)
				{
					const auto* spawnableMetaData = cl->GetMetaData("EditorSpawnable");
					if (spawnableMetaData && !spawnableMetaData->GetValue<bool>())
					{
						continue;
					}
					if (ImGui::Button(*String::Format("%s##AddComponent", *cl->Name), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetTextLineHeight() + ImGui::GetStyle().ItemSpacing.y * 2.0f)))
					{
						scene->CurrentSelectedObject->CreateAndAddComponent(cl);
					}
				}

				ImGui::EndPopup();
			}
		}

		ImGui::End();
	}
}
