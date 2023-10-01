#include "cypch.h"
#include "Class.h"

namespace Cy
{
	const ClassProperty* Class::GetPropertyFromName(const std::string& property_name) const
	{
		return &(Properties.find(property_name)->second);
	}
}