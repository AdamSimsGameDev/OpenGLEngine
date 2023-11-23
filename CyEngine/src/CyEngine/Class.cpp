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
}