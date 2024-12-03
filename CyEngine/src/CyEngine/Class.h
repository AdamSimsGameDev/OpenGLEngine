#pragma once

#include <typeinfo>
#include <unordered_map>
#include <algorithm>
#include <variant>
#include "CyEngine/String.h"

namespace Cy
{
	class Class;

	struct MetaDataProperty
	{
		enum class Type : uint8_t
		{
			Bool,
			String,
			Float,
			Int
		};

	public:
		String Key;
		std::variant<bool, int, float, String> Value;
		Type PropertyType;

		MetaDataProperty(String key, bool value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::Bool;
		}
		MetaDataProperty(String key, String value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::String;
		}		
		MetaDataProperty(String key, int value)
		{
			Key = key;
			Value = value;
			PropertyType = Type::Int;
		}		
		MetaDataProperty(String key, float value)
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
		String GetValue<String>() const
		{
			return std::get<String>(Value);
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

		bool operator==(const MetaDataProperty& other) const { return other.Key == Key; }
		bool operator==(const String& key) const { return key == Key; }
	};

	struct ClassProperty
	{
	public:
		const char* Name;
		const char* FullType;
		const char* Type;
		bool IsArray;
		bool IsFixedArray;
		bool IsEnum;
		const std::type_info* TypeInfo;
		std::vector<MetaDataProperty> MetaData;
		void(*Setter)(void*, void*);
		void*(*Getter)(const void*);

		ClassProperty(const char name[], const char full_type[], const char type[], const std::type_info* type_id, void* (*getter)(const void*), void(*setter)(void*, void*), const std::vector<MetaDataProperty>& metaData)
		{
			Name = name;
			FullType = full_type;
			Type = type;
			TypeInfo = type_id;
			Getter = getter;
			Setter = setter;
			MetaData = metaData;

			// array
			IsArray = false;
			IsFixedArray = false;

			// other props
			IsEnum = false;
		}

		template<typename T>
		T Get(const void* obj, void* src)
		{
			return *(static_cast<T*>(Getter(obj, src)));
		}

		const MetaDataProperty* GetMetaData(String key) const
		{
			for (auto it = MetaData.begin(); it != MetaData.end(); ++it)
			{
				const MetaDataProperty& m = *it;
				if (m == key)
				{
					return &m;
				}
			}
			return nullptr;
		}

		template<typename T>
		bool IsType() const
		{
			return String(Type) == T::GetStaticClass()->Name;
		}

		bool IsPointer() const
		{
			return String(Type).Contains('*');
		}

		const Class* GetClass() const;
	};

	typedef std::pair<String, std::unordered_map<int, String>> EnumInfo;

	class Class
	{
	public:
		String Name;
		const Class* ParentClass;
		std::vector<ClassProperty> Properties;
		std::vector<MetaDataProperty> MetaData;

		void AddMetaData(MetaDataProperty metaData)
		{
			for (auto it = MetaData.begin(); it != MetaData.end(); ++it)
			{
				MetaDataProperty& m = *it;
				if (m == metaData.Key)
				{
					m.Value = metaData.Value;
					return;
				}
			}

			MetaData.push_back(metaData);
		}

		template<typename T>
		T* New() const { return (T*)New(); }
		virtual void* New() const { return nullptr; }

		template<typename T>
		const T* GetClassDefaultObject() const { return (T*)ClassDefaultObject; }
		template<typename T>
		T* GetClassDefaultObject_Mutable() { return (T*)ClassDefaultObject; }

		template<class T>
		bool IsChildOf() const { return IsChildOf(T::GetStaticClass()); }
		bool IsChildOf(const Class* Other) const;

		template<class T>
		static Array<const Class*> GetChildClassesOfType() { return GetChildClassesOfType(T::GetStaticClass()); }
		static Array<const Class*> GetChildClassesOfType(const Class* Cl);

		bool IsAbstract() const;

		const ClassProperty* GetPropertyFromName(String property_name) const;

		static const Class* GetClassFromName(String class_name);
		static bool GetEnumFromName(String enum_name, EnumInfo& outInfo);
		static int GetEnumLength(String enum_name);
		static String GetEnumElementName(String enum_name, int index);
		static int GetEnumElementValue(String enum_name, int index);
		static int GetEnumValueIndex(String enum_name, int value);

		template<typename ValueType>
		const ValueType* GetPropertyValueFromName(String property_name, const void* obj) const
		{
			const auto* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || prop->TypeInfo != &typeid(ValueType))
			{
				return nullptr;
			}
			return reinterpret_cast<const ValueType*>(prop->Getter(reinterpret_cast<void*>(obj)));
		}
		void* GetPropertyValuePtrFromName(String property_name, String property_type, void* obj) const
		{
			Array<String> spl = String::Split(property_name, '.');
			const auto* prop = GetPropertyFromName(spl[0]);
			if (prop == nullptr || (!prop->IsEnum && (String(prop->Type) != property_type && !prop->GetClass()->IsChildOf(Class::GetClassFromName(property_type)))))
			{
				return nullptr;
			}
			return spl.Count() > 1 ? GetArrayElementValuePtrFromName(spl[0], prop->Type, obj, std::stoi(spl[1])) : prop->Getter(obj);
		}

		template<typename ValueType>
		static String ScrapeValueTypeName()
		{
			const std::type_info& t = typeid(ValueType);
			String str = String(t.name());
			String str2 = String::Split(str, ':').Last();
			return String::Split(str2, ' ').First();
		}

		template<typename ValueType>
		void* GetPropertyValuePtrFromName(String property_name, void* obj) const
		{
			return GetPropertyValuePtrFromName(property_name, ScrapeValueTypeName<ValueType>(), obj);
		}		
		
		template<typename ValueType>
		ValueType* GetPropertyValueFromName(String property_name, void* obj) const
		{
			return reinterpret_cast<ValueType*>(GetPropertyValuePtrFromName<ValueType>(property_name, obj));
		}
		template<typename ValueType>
		ValueType* GetPropertyValueFromName(String property_name, String property_type, void* obj) const
		{
			return reinterpret_cast<ValueType*>(GetPropertyValuePtrFromName(property_name, property_type, obj));
		}

		void* GetArrayElementValuePtrFromName(String property_name, String property_type, const void* obj, size_t index) const
		{
			const ClassProperty* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || !prop->IsArray || String(prop->Type) != property_type)
			{
				return nullptr;
			}
			ArrayBase* arr = reinterpret_cast<ArrayBase*>(prop->Getter(obj));
			if (index < 0 || index >= arr->Count())
			{
				return nullptr;
			}
			char* c = reinterpret_cast<char*>(arr->GetArrStartPtr());
			return c + (index * arr->GetElementSize());
		}

		int GetArraySizeFromName(String property_name, String property_type, void* obj) const
		{
			const ClassProperty* prop = GetPropertyFromName(property_name);
			if (prop == nullptr || !prop->IsArray || String(prop->Type) != property_type)
			{
				return 0;
			}
			ArrayBase* arr = reinterpret_cast<ArrayBase*>(prop->Getter(obj));
			return arr->Count();
		}

		const MetaDataProperty* GetMetaData(String key) const
		{
			for (auto it = MetaData.begin(); it != MetaData.end(); ++it)
			{
				const MetaDataProperty& m = *it;
				if (m == key)
				{
					return &m;
				}
			}
			return nullptr;
		}

	protected:
		void* ClassDefaultObject = nullptr;
	};
}
