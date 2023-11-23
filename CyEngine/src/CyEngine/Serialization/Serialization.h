#pragma once
#include <string>
#include <fstream>
#include "CyEngine/String.h"

#define DEFINE_SERIALIZABLE_OBJECT(ObjectType) bool ObjectType##::reg = ObjectType##::Init();

namespace Cy
{
	class SerializableBase
	{
		friend class Serialization;

	public:
		virtual void Serialize(const void* obj, String& buffer) const = 0;
		virtual void Deserialize(const String& buffer, void* out) const = 0;
	protected:
		virtual String GetType() const { return "NULL"; }
	};

	template<typename T1, typename T2>
	struct Serializable : SerializableBase
	{
	public:
		Serializable()
		{
			reg;
		}
		static bool reg;
		static bool Init()
		{
			T1* t = new T1();
			Serialization::GetSerializableObjects().emplace(t->GetType(), t);
			return true;
		}

		virtual void Serialize(const void* obj, String& buffer) const override final
		{
			Serialize(*reinterpret_cast<const T2*>(obj), buffer);
		}
		virtual void Serialize(const T2 val, String& buffer) const { };

		virtual void Deserialize(const String& buffer, void* out) const override final
		{
			Deserialize(buffer, *reinterpret_cast<T2*>(out));
		}
		virtual void Deserialize(const String& buffer, T2& out) const { };
	};

	class Serialization
	{
	public:
		static const SerializableBase* FindSerializableProperty(String type);

		static std::unordered_map<String, SerializableBase*>& GetSerializableObjects()
		{
			static std::unordered_map<String, SerializableBase*> so;
			return so;
		}
	};

	// primitive types
	struct SerializableInt : Serializable<SerializableInt, int>
	{
		virtual String GetType() const { return "int"; }
		virtual void Serialize(const int val, String& buffer) const override
		{
			buffer += std::to_string(val);
		}
		virtual void Deserialize(const String& buffer, int& out) const override
		{
			out = std::stoi(buffer);
		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableInt)

	struct SerializableFloat : Serializable<SerializableFloat, float>
	{
		virtual String GetType() const { return "float"; }
		virtual void Serialize(const float val, String& buffer) const override
		{
			buffer += std::to_string(val);
		}		
		virtual void Deserialize(const String& buffer, float& out) const override
		{
			out = std::stof(buffer);
		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableFloat)

	struct SerializableString : Serializable<SerializableString, String>
	{
		virtual String GetType() const { return "String"; }
		virtual void Serialize(const String val, String& buffer) const override
		{
			buffer += String::Format("\"%s\"", *val);
		}
		virtual void Deserialize(const String& buffer, String& out) const override
		{
			out = buffer.Substring(1, buffer.Length() - 2);
		}
	};	
	DEFINE_SERIALIZABLE_OBJECT(SerializableString)

}