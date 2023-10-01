#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/CoreMinimal.h"
#include <unordered_map>

namespace Cy
{
	struct ClassProperty
	{
	public:
		std::string Name;
		std::string Type;
		const std::type_info* TypeInfo;
		void(*Setter)(void*, void*);
		void* (*Getter)(void*);

		ClassProperty(const char name[], const char type[], const std::type_info* type_id, void* (*getter)(void*), void(*setter)(void*, void*))
		{
			Name = name;
			Type = type;
			TypeInfo = type_id;
			Getter = getter;
			Setter = setter;
		}

		template<typename T>
		T Get(void* obj, void* src)
		{
			return *(static_cast<T*>(Getter(obj, src)));
		}
	};

	class Class
	{
	public:
		std::string Name;
		std::unordered_map<std::string, ClassProperty> Properties;

		const ClassProperty* GetPropertyFromName(const std::string& property_name) const;

		template<typename ObjectType, typename ValueType>
		void SetPropertyValueFromName(const std::string& property_name, ObjectType* obj, ValueType value) const
		{
			const auto* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || prop->TypeInfo != &typeid(ValueType))
			{
				return;
			}
			prop->Setter(reinterpret_cast<void*>(obj), reinterpret_cast<void*>(value));
		}
		template<typename ObjectType, typename ValueType>
		const ValueType* GetPropertyValueFromName(const std::string& property_name, const ObjectType* obj) const
		{
			const auto* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || prop->TypeInfo != &typeid(ValueType))
			{
				return nullptr;
			}
			return reinterpret_cast<const ValueType*>(prop->Getter(reinterpret_cast<void*>(obj)));
		}
		template<typename ObjectType, typename ValueType>
		ValueType* GetPropertyValueFromName(const std::string& property_name, ObjectType* obj) const
		{
			const auto* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || prop->TypeInfo != &typeid(ValueType))
			{
				return nullptr;
			}
			return reinterpret_cast<ValueType*>(prop->Getter(reinterpret_cast<void*>(obj)));
		}
	};
}
