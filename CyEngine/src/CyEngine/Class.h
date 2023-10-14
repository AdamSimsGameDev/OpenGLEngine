#pragma once

#include <string>
#include <typeinfo>
#include <unordered_map>

namespace Cy
{
	struct ClassProperty
	{
	public:
		const char* Name;
		const char* Type;
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

		const ClassProperty* GetPropertyFromName(std::string property_name) const;

		static const Class* GetClassFromName(std::string class_name);

		template<typename ObjectType, typename ValueType>
		const ValueType* GetPropertyValueFromName(std::string property_name, const ObjectType* obj) const
		{
			const auto* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || prop->TypeInfo != &typeid(ValueType))
			{
				return nullptr;
			}
			return reinterpret_cast<const ValueType*>(prop->Getter(reinterpret_cast<void*>(obj)));
		}
		template<typename ObjectType, typename ValueType>
		ValueType* GetPropertyValueFromName(std::string property_name, ObjectType* obj) const
		{
			std::vector<std::string> spl = split(property_name, '|');
			const ClassProperty* prop = nullptr;
			const Class* currentClass = this;
			void* obj_ptr = reinterpret_cast<void*>(obj);
			for (const auto& str : spl)
			{
				prop = currentClass->GetPropertyFromName(str);
				if (prop == nullptr)
				{
					return nullptr;
				}

				if (prop->TypeInfo == &typeid(ValueType))
				{
					break;
				}

				const Class* foundClass = GetClassFromName(prop->Type);
				if (!foundClass)
				{
					return nullptr;
				}

				currentClass = foundClass;
				obj_ptr = prop->Getter(obj_ptr);
			}
			if (prop->TypeInfo != &typeid(ValueType))
			{
				return nullptr;
			}
			return reinterpret_cast<ValueType*>(prop->Getter(obj_ptr));
		}

	private:
		static std::vector<std::string> split(const std::string str, const char& separator)
		{
			std::vector<std::string> outstr;
			std::string cur;
			for (const auto& ch : str)
			{
				if (ch == separator)
				{
					if (cur.length() > 0)
						outstr.push_back(cur);
					cur = "";
				}
				else
				{
					cur += ch;
				}
			}
			if (cur.length() > 0)
				outstr.push_back(cur);
			return outstr;
		}
	};
}
