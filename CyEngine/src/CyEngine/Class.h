#pragma once

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <algorithm>
#include <variant>

namespace Cy
{
	struct ClassPropertyMetaData
	{
		enum Type
		{
			Bool,
			String,
			Float,
			Int
		};

	public:
		std::string Key;
		std::variant<bool, int, float, std::string> Value;
		Type PropertyType;

		ClassPropertyMetaData(std::string key, bool value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::Bool;
		}
		ClassPropertyMetaData(std::string key, std::string value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::String;
		}		
		ClassPropertyMetaData(std::string key, int value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::Int;
		}		
		ClassPropertyMetaData(std::string key, float value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::Float;
		}

		template<typename T>
		T GetValue() const { return default(T); }

		template<>
		bool GetValue<bool>() const
		{
			return std::get<bool>(Value);
		}
		template<>
		std::string GetValue<std::string>() const
		{
			return std::get<std::string>(Value);
		}
		template<>
		float GetValue<float>() const
		{
			return std::get<float>(Value);
		}
		template<>
		int GetValue<int>() const
		{
			return std::get<int>(Value);
		}

		bool operator==(const ClassPropertyMetaData& other) const { return !other.Key.compare(Key); }
		bool operator==(const std::string& key) const { return !key.compare(Key); }
	};

	struct ClassProperty
	{
	public:
		const char* Name;
		const char* Type;
		const std::type_info* TypeInfo;
		std::vector<ClassPropertyMetaData> MetaData;
		void(*Setter)(void*, void*);
		void* (*Getter)(void*);

		ClassProperty(const char name[], const char type[], const std::type_info* type_id, void* (*getter)(void*), void(*setter)(void*, void*), const std::vector<ClassPropertyMetaData>& metaData)
		{
			Name = name;
			Type = type;
			TypeInfo = type_id;
			Getter = getter;
			Setter = setter;
			MetaData = metaData;
		}

		template<typename T>
		T Get(void* obj, void* src)
		{
			return *(static_cast<T*>(Getter(obj, src)));
		}

		const ClassPropertyMetaData* GetMetaData(std::string key) const
		{
			for (auto it = MetaData.begin(); it != MetaData.end(); ++it)
			{
				const ClassPropertyMetaData& m = *it;
				if (m == key)
				{
					return &m;
				}
			}
			return nullptr;
		}
	};

	class Class
	{
	public:
		std::string Name;
		std::unordered_map<std::string, ClassProperty> Properties;

		const ClassProperty* GetPropertyFromName(std::string property_name) const;

		static const Class* GetClassFromName(std::string class_name);

		template<typename ValueType>
		const ValueType* GetPropertyValueFromName(std::string property_name, const void* obj) const
		{
			const auto* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || prop->TypeInfo != &typeid(ValueType))
			{
				return nullptr;
			}
			return reinterpret_cast<const ValueType*>(prop->Getter(reinterpret_cast<void*>(obj)));
		}

		void* GetPropertyValuePtrFromName(std::string property_name, std::string property_type, void* obj) const
		{
			std::vector<std::string> spl = split(property_name, '|');
			const ClassProperty* prop = nullptr;
			const Class* currentClass = this;
			for (const auto& str : spl)
			{
				prop = currentClass->GetPropertyFromName(str);
				if (prop == nullptr)
				{
					return nullptr;
				}

				if (prop->Type == property_type)
				{
					break;
				}

				const Class* foundClass = GetClassFromName(prop->Type);
				if (!foundClass)
				{
					return nullptr;
				}

				currentClass = foundClass;
				obj = prop->Getter(obj);
			}
			return prop->Getter(obj);
		}
		template<typename ValueType>
		void* GetPropertyValuePtrFromName(std::string property_name, void* obj) const
		{
			std::vector<std::string> spl = split(property_name, '|');
			const ClassProperty* prop = nullptr;
			const Class* currentClass = this;
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
				obj = prop->Getter(obj);
			}
			return prop->Getter(obj);
		}

		template<typename ValueType>
		ValueType* GetPropertyValueFromName(std::string property_name, void* obj) const
		{
			return reinterpret_cast<ValueType*>(GetPropertyValuePtrFromName<ValueType>(property_name, obj));
		}
		template<typename ValueType>
		ValueType* GetPropertyValueFromName(std::string property_name, std::string property_type, void* obj) const
		{
			return reinterpret_cast<ValueType*>(GetPropertyValuePtrFromName(property_name, property_type, obj));
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
