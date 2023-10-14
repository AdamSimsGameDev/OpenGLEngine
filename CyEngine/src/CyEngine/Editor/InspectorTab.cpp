#include "cypch.h"
#include "InspectorTab.h"
#include <imgui.h>
#include "CyEngine/Application.h"
#include "CyEngine/Components/Component.h"
#include "CyEngine/Objects/SceneObject.h"
#include "CyEngine/Scene.h"

namespace Cy
{
	bool InspectorTab::RenderProperty(Object* obj, const String& prefix, const std::pair<String, ClassProperty>& prop)
	{
		const Class* cl = obj->GetClass();
		if (int* i = cl->GetPropertyValueFromName<Object, int>(prefix + prop.first, obj))
		{
			ImGui::DragInt(*prop.first, i);
			return true;
		}
		else if (float* i = cl->GetPropertyValueFromName<Object, float>(prefix + prop.first, obj))
		{
			ImGui::DragFloat(*prop.first, i);
			return true;
		}
		else if (bool* i = cl->GetPropertyValueFromName<Object, bool>(prefix + prop.first, obj))
		{
			ImGui::Checkbox(*prop.first, i);
			return true;
		}
		else if (Vector3* i = cl->GetPropertyValueFromName<Object, Vector3>(prefix + prop.first, obj))
		{
			float pos[3]{ i->x, i->y, i->z };
			ImGui::DragFloat3(*prop.first, pos);
			i->x = pos[0];
			i->y = pos[1];
			i->z = pos[2];
			return true;
		}
		else if (Quat* i = cl->GetPropertyValueFromName<Object, Quat>(prefix + prop.first, obj))
		{
			Vector3 v = Quat::ToEuler(*i);
			float rot[3]{ v.x, v.y, v.z };
			ImGui::DragFloat3(*prop.first, rot);
			*i = Quat::FromEuler({ rot[0], rot[1], rot[2] });
			return true;
		}
		else if (String* i = cl->GetPropertyValueFromName<Object, String>(prefix + prop.first, obj))
		{
			ImGui::InputText(*prop.first, *(*i), 256);
			return true;
		}
		return false;
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
