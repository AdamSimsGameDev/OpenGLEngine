#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/Class.h"

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
		static std::string ConvertToJson(T type)
		{
			// need some way of getting the serialization info for the type.
			// either this is a STRUCT or a CLASS and has serialization info.
			Class* cl = type.GetClass();
			std::string s;
			ConvertToJsonInternal(t, cl, s);
			return s;
		}

	private:
		std::string add_indent(int count) const
		{
			std::string s;
			for (int i = 0; i < count; i++)
				s += "\t";
			return s;
		}

		template<typename T>
		static void ConvertToJsonInternal(T type, Class* cl, std::string& str, int indent = 0)
		{
			str += "{\n";
			// loop over the properties.
			for (const auto& prop : cl->Properties)
			{
				str += add_indent(indent + 1);
				str += "\"" + prop.first + "\":";
				if (Class* ncl = Class::GetClassFromName(prop.second.Type))
				{

				}
				else
				{

				}
			}
			str += "}";
		}
	};
}
