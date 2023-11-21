#pragma once
#include <string>
#include <fstream>
#include "CyEngine/Class.h"

#define DEFINE_SERIALIZABLE_OBJECT(ObjectType) bool ObjectType##::reg = ObjectType##::Init();

namespace Cy
{
	class Object;

	template<typename Type>
	class SerializationBuffer
	{
	public:
		SerializationBuffer(std::string path)
		{
			Stream = Type(path);
		}

		virtual void Write(std::string in) {}
		virtual void Read(std::string out) {}

		void Close()
		{
			Stream.close();
		}

	protected: 
		Type Stream;
	};

	class SerializationBufferWrite : public SerializationBuffer<std::ofstream>
	{
	public:
		SerializationBufferWrite(std::string path) : SerializationBuffer(path)
		{
		}

		virtual void Write(std::string in) override
		{
			Stream << in;
		}

	private:
		int m_WriteCount = 0;
	};	
	
	class SerializationBufferRead : public SerializationBuffer<std::ifstream>
	{
	public:
		SerializationBufferRead(std::string path) : SerializationBuffer(path)
		{
		}

		virtual void Read(std::string out) override
		{
			std::getline(Stream, out);
		}
	};

	class SerializableBase
	{
		friend class Serialization;

	public:
		virtual void Serialize(const void* obj, std::string& buffer) const = 0;
	protected:
		virtual std::string GetType() const { return "NULL"; }
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

		virtual void Serialize(const void* obj, std::string& buffer) const override final
		{
			Serialize(*reinterpret_cast<const T2*>(obj), buffer);
		}
		virtual void Serialize(const T2 val, std::string& buffer) const { };
	};

	class Serialization
	{
	public:
		static const SerializableBase* FindSerializableProperty(std::string type);

		static std::unordered_map<std::string, SerializableBase*>& GetSerializableObjects()
		{
			static std::unordered_map<std::string, SerializableBase*> so;
			return so;
		}
	};

	// primitive types
	struct SerializableInt : Serializable<SerializableInt, int>
	{
		virtual std::string GetType() const { return "int"; }
		virtual void Serialize(const int val, std::string& buffer) const override
		{
			buffer += std::to_string(val);
		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableInt)

	struct SerializableFloat : Serializable<SerializableFloat, float>
	{
		virtual std::string GetType() const { return "float"; }
		virtual void Serialize(const float val, std::string& buffer) const override
		{
			buffer += std::to_string(val);
		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableFloat)
}