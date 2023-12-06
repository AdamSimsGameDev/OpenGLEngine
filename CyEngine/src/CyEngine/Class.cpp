#include "cypch.h"
#include "Class.h"
#include "generated/ClassLibrary.h"

namespace Cy
{
	const ClassProperty* Class::GetPropertyFromName(String property_name) const
	{
		return &(Properties.find(property_name)->second);
	}

	const Class* Class::GetClassFromName(String class_name)
	{
		if (ClassLibrary::ClassMap.find(class_name) != ClassLibrary::ClassMap.end())
		{
			return ClassLibrary::ClassMap[class_name]();
		}
		return nullptr;
	}

	bool Class::GetEnumFromName(String enum_name, EnumInfo& outInfo)
	{
		if (ClassLibrary::EnumMap.find(enum_name) != ClassLibrary::EnumMap.end())
		{
			outInfo = EnumInfo(enum_name, ClassLibrary::EnumMap[enum_name]);
			return true;
		}
		outInfo = EnumInfo();
		return false;
	}

	int Class::GetEnumLength(String enum_name)
	{
		EnumInfo info;
		if (!GetEnumFromName(enum_name, info))
		{
			return 0;
		}
		return (int)info.second.size();
	}

	String Class::GetEnumElementName(String enum_name, int index)
	{
		EnumInfo info;
		if (!GetEnumFromName(enum_name, info))
		{
			return "";
		}
		Array<String> names;
		for (auto k : info.second)
		{
			names.Emplace(k.second);
		}
		return names[index];
	}

	int Class::GetEnumElementValue(String enum_name, int index)
	{
		EnumInfo info;
		if (!GetEnumFromName(enum_name, info))
		{
			return -1;
		}
		Array<int> values;
		for (auto k : info.second)
		{
			values.Emplace(k.first);
		}
		return values[index];
	}
	int Class::GetEnumValueIndex(String enum_name, int value)
	{
		EnumInfo info;
		if (!GetEnumFromName(enum_name, info))
		{
			return -1;
		}
		int counter = 0;
		for (auto k : info.second)
		{
			if (k.first == value)
			{
				return counter;
			}
			counter++;
		}
		return -1;
	}
}