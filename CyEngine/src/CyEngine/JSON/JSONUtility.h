#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/Class.h"
#include "CyEngine/Serialization/Serialization.h"

namespace Cy
{
	// Parsing to JSON should be fairly simple, recursing over the data and constructing the .json file.
	// In order to parse from JSON we need two things.
	// - A library that handles the parsing, and constructs an object.
	// - An object that holds the parsed data.

	class JSONUtility
	{
	public:
		template<typename T>
		static std::string ConvertToJson(T* obj)
		{
			// need some way of getting the serialization info for the type.
			// either this is a STRUCT or a CLASS and has serialization info.
			Class* cl = type.GetClass();
			std::string s;
			ConvertToJsonInternal(obj, cl, s);
			return s;
		}
		static std::string ConvertToJson(void* obj, const Class* cl)
		{
			// need some way of getting the serialization info for the type.
			// either this is a STRUCT or a CLASS and has serialization info.
			std::string s;
			ConvertToJsonInternal(obj, cl, s);
			return s;
		}

		template<typename T>
		static void ConvertFromJson(std::string json, void* target)
		{
			return ConvertFromJson(json, target, T::StaticClass());
		}
		static void ConvertFromJson(std::string json, void* target, const Class* cl)
		{
			ConvertFromJsonInternal(json, cl, target);
		}

	private:
		static std::string add_indent(int count)
		{
			std::string s;
			for (int i = 0; i < count; i++)
				s += "\t";
			return s;
		}

		static void ConvertToJsonInternal(void* obj, const Class* cl, std::string& buffer, int indent = 0)
		{
			buffer += add_indent(indent) + "{\n";
			// loop over the properties.
			int count = 0;
			for (const auto& prop : cl->Properties)
			{
				if (count != 0)
					buffer += ",\n";
				buffer += add_indent(indent + 1);
				buffer += "\"" + prop.first + "\":";
				if (const SerializableBase* serializable = Serialization::FindSerializableProperty(prop.second.Type))
				{
					serializable->Serialize(prop.second.Getter(obj), String(buffer));
				}
				else if (const Class* ncl = Class::GetClassFromName(prop.second.Type))
				{
					buffer += "\n";
					void* n = cl->GetPropertyValuePtrFromName(prop.first, prop.second.Type, obj);
					ConvertToJsonInternal(n, ncl, buffer, indent + 1);
				}
				count++;
			}
			buffer += "\n";
			buffer += add_indent(indent) + "}";
		}

		static void ConvertFromJsonInternal(std::string json, const Class* cl, void* obj)
		{
			std::unordered_map<std::string, std::string> props;
			int start_offset = 0;
			std::string key;
			std::string value;
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
						key.clear();
						value.clear();
						continue;
					}
					else if (c == '"')
					{
						is_quoted = !is_quoted;
					}
					else if (c == '{' || c == '(')
					{
						value_indent++;
					}
					else if (c == '}' || c == ')')
					{
						value_indent--;
						if (value_indent == -1)
						{
							is_key = true;
							props.emplace(key, value);
							key.clear();
							value.clear();
							continue;
						}
					}
					if (c != '\n' && c != '\t' && (is_quoted || c != ' '))
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
	};
}
