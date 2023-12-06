#include "cypch.h"
#include "PropertyField.h"
#include "CyEngine/Objects/Object.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Cy
{
	std::unordered_map<String, PropertyFieldBase*> PropertyFieldBase::PropertyFields;

	void ItemLabel(String title)
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		const ImVec2 lineStart = ImGui::GetCursorScreenPos();
		const ImGuiStyle& style = ImGui::GetStyle();
		float fullWidth = ImGui::GetContentRegionAvail().x;
		float itemWidth = ImGui::CalcItemWidth() + style.ItemSpacing.x;
		ImVec2 textSize = ImGui::CalcTextSize(*title, &title[title.Length() - 1]);
		ImRect textRect;
		textRect.Min = ImGui::GetCursorScreenPos();
		textRect.Max = textRect.Min;
		textRect.Max.x += fullWidth - itemWidth;
		textRect.Max.y += textSize.y;

		ImGui::SetCursorScreenPos(textRect.Min);

		ImGui::AlignTextToFramePadding();
		// Adjust text rect manually because we render it directly into a drawlist instead of using public functions.
		textRect.Min.y += window->DC.CurrLineTextBaseOffset;
		textRect.Max.y += window->DC.CurrLineTextBaseOffset;

		ImGui::ItemSize(textRect);
		if (ImGui::ItemAdd(textRect, window->GetID(*title, *title + title.Length())))
		{
			ImGui::RenderTextEllipsis(ImGui::GetWindowDrawList(), textRect.Min, textRect.Max, textRect.Max.x,
				textRect.Max.x, *title, *title + title.Length(), &textSize);

			if (textRect.GetWidth() < textSize.x && ImGui::IsItemHovered())
				ImGui::SetTooltip("%.*s", (int)title.Length(), *title);
		}

		ImGui::SetCursorScreenPos(ImVec2{ textRect.Max.x - 0, textRect.Max.y - textSize.y + window->DC.CurrLineTextBaseOffset });
		ImGui::SameLine();
	}


	DEFINE_PROPERTY_FIELD(PropertyFieldInt);
	bool PropertyFieldInt::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (int* i = cl->GetPropertyValueFromName<int>(prop.first, obj))
		{
			ItemLabel(prop.first);
			ImGui::DragInt(*String::Format("##%s", *prop.first), i);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldFloat);
	bool PropertyFieldFloat::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (float* i = cl->GetPropertyValueFromName<float>(prop.first, obj))
		{
			ItemLabel(prop.first);
			ImGui::DragFloat(*String::Format("##%s", *prop.first), i);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldBool);
	bool PropertyFieldBool::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (bool* i = cl->GetPropertyValueFromName<bool>(prop.first, obj))
		{
			ItemLabel(prop.first);
			ImGui::Checkbox(*String::Format("##%s", *prop.first), i);
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldString);
	bool PropertyFieldString::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (String* i = cl->GetPropertyValueFromName<String>(prop.first, obj))
		{
			char* i_copy = new char[i->Length() + 1];
			strcpy(i_copy, **i);
			i_copy[i->Length()] = '\0';
			ItemLabel(prop.first);
			ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 16 - ImGui::GetStyle().ItemSpacing.x);
			ImGui::InputText(*String::Format("##%s", *prop.first), i_copy, 256);
			if (*i != i_copy)
			{
				*i = String(i_copy);
			}
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector2);
	bool PropertyFieldVector2::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (Vector2* i = cl->GetPropertyValueFromName<Vector2>(prop.first, obj))
		{
			ItemLabel(prop.first);
			float pos[2]{ i->x, i->y };
			ImGui::DragFloat2(*String::Format("##%s", *prop.first), pos);
			i->x = pos[0];
			i->y = pos[1];
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector3);
	bool PropertyFieldVector3::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (Vector3* i = cl->GetPropertyValueFromName<Vector3>(prop.first, obj))
		{
			ItemLabel(prop.first);
			float pos[3]{ i->x, i->y, i->z };
			ImGui::DragFloat3(*String::Format("##%s", *prop.first), pos);
			i->x = pos[0];
			i->y = pos[1];
			i->z = pos[2];
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector4);
	bool PropertyFieldVector4::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (Vector4* i = cl->GetPropertyValueFromName<Vector4>(prop.first, obj))
		{
			ItemLabel(prop.first);
			float pos[4]{ i->x, i->y, i->z, i->w };
			ImGui::DragFloat3(*String::Format("##%s", *prop.first), pos);
			i->x = pos[0];
			i->y = pos[1];
			i->z = pos[2];
			i->w = pos[3];
			return true;
		}
		return false;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldQuat);
	bool PropertyFieldQuat::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		if (Quat* i = cl->GetPropertyValueFromName<Quat>(prop.first, obj))
		{
			ItemLabel(prop.first);
			Vector3 v = Quat::ToEuler(*i);
			float rot[3]{ v.x, v.y, v.z };
			ImGui::DragFloat3(*String::Format("##%s", *prop.first), rot);
			*i = Quat::FromEuler({ rot[0], rot[1], rot[2] });
			return true;
		}
		return false;
	}

	static bool ArrayStrGetter(void* data, int n, const char** out_str) 
	{ 
		*out_str = *((const String*)data)[n]; 
		return true; 
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldEnum);
	bool PropertyFieldEnum::RenderProperty(void* obj, const Class* cl, const std::pair<String, ClassProperty>& prop) const
	{
		// get the enum value from the name.
		if (int* i = cl->GetPropertyValueFromName<int>(prop.first, obj))
		{
			Array<String> items;
			int size = Class::GetEnumLength(prop.second.Type);
			for (int i = 0; i < size; i++)
			{
				items.Add(Class::GetEnumElementName(prop.second.Type, i));
			}

			int index = Class::GetEnumValueIndex(prop.second.Type, *i);

			ItemLabel(prop.first);
			ImGui::Combo(*String::Format("##%s", *prop.first), &index, &ArrayStrGetter, *items, size);

			// update i to the new value
			*i = Class::GetEnumElementValue(prop.second.Type, index);

			return true;
		}
		return false;
	}
}
