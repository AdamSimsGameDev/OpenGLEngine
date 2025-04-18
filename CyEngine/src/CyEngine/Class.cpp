#include "cypch.h"
#include "Class.h"
#include "generated/ClassLibrary.h"

namespace Cy
{
	bool Class::IsChildOf(const Class* Other) const
	{
		if (Other == nullptr)
			return false;

		if (Other == this)
			return true;

		const Class* p = ParentClass;
		while (p)
		{
			if (p == Other)
			{
				return true;
			}
			p = p->ParentClass;
		}

		return false;
	}

	Array<const Class*> Class::GetChildClassesOfType(const Class* Cl)
	{
		Array<const Class*> classes;
		for (const auto& pair : ClassLibrary::ClassMap)
		{
			const Class* c = pair.second();
			if (c->IsChildOf(Cl) && c != Cl)
			{
				classes.Add(c);
			}
		}
		return classes;
	}

	bool Class::IsAbstract() const
	{
		const MetaDataProperty* property = GetMetaData("Abstract");
		return property && property->GetValue<bool>() == true;
	}

	const ClassProperty* Class::GetPropertyFromName(String property_name) const
	{
		for (const auto& prop : Properties)
		{
			if (String(prop.Name) == property_name)
			{
				return &prop;
			}
		}
		return nullptr;
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

	const Class* ClassProperty::GetClass() const
	{
		String CurType = Type;
		if (IsPointer())
		{
			CurType = CurType.ReplaceLast("*", "");
		}

		return Class::GetClassFromName(CurType);
	}
}