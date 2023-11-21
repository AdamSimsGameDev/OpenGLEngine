#include "cypch.h"
#include "PropertyField.h"
#include "CyEngine/Objects/Object.h"
#include <imgui.h>

namespace Cy
{
	std::unordered_map<std::string, PropertyFieldBase*> PropertyFieldBase::PropertyFields;

	DEFINE_PROPERTY_FIELD(PropertyFieldInt);
	bool PropertyFieldInt::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (int* i = cl->GetPropertyValueFromName<int>(path, obj))
		{
			ImGui::DragInt(*prop.first, i);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldFloat);
	bool PropertyFieldFloat::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (float* i = cl->GetPropertyValueFromName<float>(path, obj))
		{
			ImGui::DragFloat(*prop.first, i);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldBool);
	bool PropertyFieldBool::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (bool* i = cl->GetPropertyValueFromName<bool>(path, obj))
		{
			ImGui::Checkbox(*prop.first, i);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldString);
	bool PropertyFieldString::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (String* i = cl->GetPropertyValueFromName<String>(path, obj))
		{
			ImGui::InputText(*prop.first, *(*i), 256);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector2);
	bool PropertyFieldVector2::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (Vector2* i = cl->GetPropertyValueFromName<Vector2>(path, obj))
		{
			float pos[2]{ i->x, i->y };
			ImGui::DragFloat2(*prop.first, pos);
			i->x = pos[0];
			i->y = pos[1];
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector3);
	bool PropertyFieldVector3::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (Vector3* i = cl->GetPropertyValueFromName<Vector3>(path, obj))
		{
			float pos[3]{ i->x, i->y, i->z };
			ImGui::DragFloat3(*prop.first, pos);
			i->x = pos[0];
			i->y = pos[1];
			i->z = pos[2];
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector4);
	bool PropertyFieldVector4::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (Vector4* i = cl->GetPropertyValueFromName<Vector4>(path, obj))
		{
			float pos[4]{ i->x, i->y, i->z, i->w };
			ImGui::DragFloat3(*prop.first, pos);
			i->x = pos[0];
			i->y = pos[1];
			i->z = pos[2];
			i->w = pos[3];
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldQuat);
	bool PropertyFieldQuat::RenderProperty(Object* obj, const String& path, const std::pair<String, ClassProperty>& prop) const
	{
		const Class* cl = obj->GetClass();
		if (Quat* i = cl->GetPropertyValueFromName<Quat>(path, obj))
		{
			Vector3 v = Quat::ToEuler(*i);
			float rot[3]{ v.x, v.y, v.z };
			ImGui::DragFloat3(*prop.first, rot);
			*i = Quat::FromEuler({ rot[0], rot[1], rot[2] });
			return true;
		}
		return false;
	}
}
