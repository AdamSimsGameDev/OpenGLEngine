#pragma once
#include "cypch.h"
#include "JSONUtility.h"
#include "CyEngine/Class.h"
#include "CyEngine/Serialization/Serialization.h"

namespace Cy
{
	String add_indent(int count)
	{
		String s;
		for (int i = 0; i < count; i++)
			s += "\t";
		return s;
	}

	void JSONUtility::ConvertToJsonInternal(void* obj, const Class* cl, String& buffer, int indent)
	{
		buffer += add_indent(indent) + "{\n";
		// loop over the properties.
		int count = 0;
		for (const auto& prop : cl->Properties)
		{
			if (count != 0)
				buffer += ",\n";
			buffer += add_indent(indent + 1);
			buffer += String::Format("\"%s\":", *prop.first);
			if (const SerializableBase* serializable = Serialization::FindSerializableProperty(prop.second.Type))
			{
				if (prop.second.IsArray)
				{
					buffer += "\n";
					buffer += add_indent(indent + 1);
					buffer += "[\n";
					size_t s = cl->GetArraySizeFromName(prop.first, prop.second.Type, obj);
					for (size_t i = 0; i < s; i++)
					{
						buffer += add_indent(indent + 2);
						void* n = cl->GetPropertyValuePtrFromName(prop.first + '.' + std::to_string(i), prop.second.Type, obj);
						serializable->Serialize(n, buffer);
						if (i != s - 1)
						{
							buffer += ",\n";
						}
					}
					buffer += "\n";
					buffer += add_indent(indent + 1);
					buffer += "]";
				}
				else
				{
					serializable->Serialize(prop.second.Getter(obj), buffer);
				}
			}
			else if (const Class* ncl = Class::GetClassFromName(prop.second.Type))
			{
				if (prop.second.IsArray)
				{
					buffer += "\n";
					buffer += add_indent(indent + 1);
					buffer += "[\n";
					size_t s = cl->GetArraySizeFromName(prop.first, prop.second.Type, obj);
					for (size_t i = 0; i < s; i++)
					{
						buffer += add_indent(indent + 2);
						void* n = cl->GetPropertyValuePtrFromName(prop.first + "." + std::to_string(i), prop.second.Type, obj);
						ConvertToJsonInternal(n, ncl, buffer, indent + 1);
						if (i != s - 1)
						{
							buffer += ",\n";
						}
					}
					buffer += "\n";
					buffer += add_indent(indent + 1);
					buffer += "]";
				}
				else
				{
					buffer += "\n";
					void* n = cl->GetPropertyValuePtrFromName(prop.first, prop.second.Type, obj);
					ConvertToJsonInternal(n, ncl, buffer, indent + 1);
				}
			}
			count++;
		}
		buffer += "\n";
		buffer += add_indent(indent) + "}";
	}

	void JSONUtility::ConvertFromJsonInternal(String json, const Class* cl, void* obj)
	{
		std::unordered_map<String, String> props;
		int start_offset = 0;
		String key;
		String value;
		bool is_key = true;
		bool in_key_string = false;
		bool is_quoted = false;
		int value_indent = 0;
		for (const char& c : json)
		{
			if (is_key)
			{
				if (c == ':')
				{
					is_key = false;
				}
				else if (c == '"')
				{
					in_key_string = !in_key_string;
				}
				else if (in_key_string && c != '\n' && c != '\t')
				{
					key += c;
				}
			}
			else
			{
				if (value_indent == 0 && c == ',')
				{
					is_key = true;
					props.emplace(key, value);
					key.Empty();
					value.Empty();
					continue;
				}
				else if (c == '"')
				{
					is_quoted = !is_quoted;
				}
				else if (c == '{' || c == '(' || c == '[')
				{
					value_indent++;
				}
				else if (c == '}' || c == ')' || c == ']')
				{
					value_indent--;
					if (value_indent == -1)
					{
						is_key = true;
						props.emplace(key, value);
						key.Empty();
						value.Empty();
						continue;
					}
				}
				if (c != '\n' && c != '\t' && c != '\r' && (is_quoted || c != ' '))
				{
					value += c;
				}
			}
		}

		for (const auto& prop : props)
		{
			const ClassProperty* classProp = cl->GetPropertyFromName(prop.first);
			if (!classProp)
			{
				continue;
			}
			if (classProp->IsArray) // array
			{
				// break out the individual properties of the array.
				Array<String> spl = String::SplitUnquoted(prop.second.Substring(1, prop.second.Length() - 2), ',');
				size_t s = spl.Count();
				if (const SerializableBase* serializable = Serialization::FindSerializableProperty(classProp->Type))
				{
					if (!classProp->IsFixedArray)
					{
						ArrayBase* arr = reinterpret_cast<ArrayBase*>(cl->GetPropertyValuePtrFromName(prop.first, classProp->Type, obj));
						arr->Reserve(s);
						arr->SetSize(s);
					}
					for (size_t i = 0; i < s; i++)
					{
						void* n = cl->GetPropertyValuePtrFromName(prop.first + "." + std::to_string(i), classProp->Type, obj);
						serializable->Deserialize(spl[i], n);
					}
				}
				else if (const Class* ncl = Class::GetClassFromName(classProp->Type))
				{
					for (size_t i = 0; i < s; i++)
					{
						void* n = cl->GetPropertyValuePtrFromName(prop.first + "." + std::to_string(i), classProp->Type, obj);
						ConvertFromJsonInternal(spl[i], ncl, n);
					}
				}
			}
			else
			{
				if (const SerializableBase* serializable = Serialization::FindSerializableProperty(classProp->Type))
				{
					void* d = classProp->Getter(obj);
					serializable->Deserialize(prop.second, d);
				}
				else if (const Class* ncl = Class::GetClassFromName(classProp->Type))
				{
					void* n = cl->GetPropertyValuePtrFromName(prop.first, classProp->Type, obj);
					ConvertFromJsonInternal(prop.second, ncl, n);
				}
			}
		}
	}
}
