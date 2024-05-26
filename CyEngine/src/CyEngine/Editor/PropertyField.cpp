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
	bool PropertyFieldInt::RenderProperty(int* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		ImGui::DragInt(*String::Format("##%s_%p", *displayName, data), data);
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldFloat);
	bool PropertyFieldFloat::RenderProperty(float* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		ImGui::DragFloat(*String::Format("##%s_%p", *displayName, data), data);
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldBool);
	bool PropertyFieldBool::RenderProperty(bool* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		ImGui::Checkbox(*String::Format("##%s_%p", *displayName, data), data);
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldString);
	bool PropertyFieldString::RenderProperty(String* data, const String& displayName, const ClassProperty& info) const
	{
		char* i_copy = new char[data->Length() + 1];
		strcpy(i_copy, **data);
		i_copy[data->Length()] = '\0';
		ItemLabel(displayName);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 16 - ImGui::GetStyle().ItemSpacing.x);
		ImGui::InputText(*String::Format("##%s_%p", *displayName, data), i_copy, 256);
		if (*data != i_copy)
		{
			*data = String(i_copy);
		}
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector2);
	bool PropertyFieldVector2::RenderProperty(Vector2* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		float pos[2]{ data->x, data->y };
		ImGui::DragFloat2(*String::Format("##%s_%p", *displayName, data), pos);
		data->x = pos[0];
		data->y = pos[1];
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector3);
	bool PropertyFieldVector3::RenderProperty(Vector3* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		float pos[3]{ data->x, data->y, data->z };
		ImGui::DragFloat3(*String::Format("##%s_%p", *displayName, data), pos);
		data->x = pos[0];
		data->y = pos[1];
		data->z = pos[2];
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldVector4);
	bool PropertyFieldVector4::RenderProperty(Vector4* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		float pos[4]{ data->x, data->y, data->z, data->w };
		ImGui::DragFloat3(*String::Format("##%s_%p", *displayName, data), pos);
		data->x = pos[0];
		data->y = pos[1];
		data->z = pos[2];
		data->w = pos[3];
		return true;
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldQuat);
	bool PropertyFieldQuat::RenderProperty(Quat* data, const String& displayName, const ClassProperty& info) const
	{
		ItemLabel(displayName);
		Vector3 v = Quat::ToEuler(*data);
		float rot[3]{ v.x, v.y, v.z };
		ImGui::DragFloat3(*String::Format("##%s_%p", *displayName, data), rot);
		*data = Quat::FromEuler({ rot[0], rot[1], rot[2] });
		return true;
	}

	static bool ArrayStrGetter(void* data, int n, const char** out_str) 
	{ 
		*out_str = *((const String*)data)[n]; 
		return true; 
	}

	DEFINE_PROPERTY_FIELD(PropertyFieldEnum);
	bool PropertyFieldEnum::RenderProperty(uint8_t* data, const String& displayName, const ClassProperty& info) const
	{
		Array<String> items;
		int size = Class::GetEnumLength(info.Type);
		for (int i = 0; i < size; i++)
		{
			items.Add(Class::GetEnumElementName(info.Type, i));
		}

		int index = Class::GetEnumValueIndex(info.Type, *data);

		ItemLabel(displayName);
		ImGui::Combo(*String::Format("##%s_%p", *displayName, data), &index, &ArrayStrGetter, *items, size);

		// update i to the new value
		*data = Class::GetEnumElementValue(info.Type, index);

		return true;
	}
}
