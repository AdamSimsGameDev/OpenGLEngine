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

	struct JSONObject
	{
		enum Type
		{
			String,
			Float,
			Int,
			Bool,
			Array,
		};

	public:
		std::string key;
		Type valueType;

		template<typename T>
		T GetValue() const = 0;

	private:
		std::string stringValue;
		float floatValue;
		int intValue;
		bool boolValue;
		std::vector<JSONObject> arrValue;
	};

	template<>
	std::string JSONObject::GetValue() const { return stringValue; }
	template<>
	float JSONObject::GetValue() const { return floatValue; }
	template<>
	int JSONObject::GetValue() const { return intValue; }
	template<>
	bool JSONObject::GetValue() const { return boolValue; }
	template<>
	std::vector<JSONObject> JSONObject::GetValue() const { return arrValue; }

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
					serializable->Serialize(prop.second.Getter(obj), buffer);
				}
				else if (const Class* ncl = Class::GetClassFromName(prop.second.Type))
				{
					buffer += "\n";
					void* n = cl->GetPropertyValuePtrFromName(prop.first, prop.second.Type, obj);
					ConvertToJsonInternal(n, ncl, buffer, indent + 1);
				}
				count++;
			}
			buffer += "\n" + add_indent(indent) + "}";
		}
	};
}
