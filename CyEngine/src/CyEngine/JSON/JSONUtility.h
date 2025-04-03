#pragma once
#include "CyEngine/String.h"

namespace Cy
{
	// Parsing to JSON should be fairly simple, recursing over the data and constructing the .json file.
	// In order to parse from JSON we need two things.
	// - A library that handles the parsing, and constructs an object.
	// - An object that holds the parsed data.

	class Class;

	class JSONUtility
	{
	public:
		template<typename T>
		static String ConvertToJson(T* obj)
		{
			// need some way of getting the serialization info for the type.
			// either this is a STRUCT or a CLASS and has serialization info.
			Class* cl = obj->GetClass();
			String s;
			ConvertToJsonInternal(obj, cl, s);
			return s;
		}
		static String ConvertToJson(void* obj, const Class* cl)
		{
			// need some way of getting the serialization info for the type.
			// either this is a STRUCT or a CLASS and has serialization info.
			String s;
			ConvertToJsonInternal(obj, cl, s);
			return s;
		}

		template<typename T>
		static void ConvertFromJson(String json, void* target)
		{
			return ConvertFromJson(json, target, T::GetStaticClass());
		}
		static void ConvertFromJson(String json, void* target, const Class* cl)
		{
			ConvertFromJsonInternal(json, cl, target);
		}

	private:
		static void ConvertToJsonInternal(void* obj, const Class* cl, String& buffer, int indent = 0);
		static void ConvertFromJsonInternal(String json, const Class* cl, void* obj);
	};
}
