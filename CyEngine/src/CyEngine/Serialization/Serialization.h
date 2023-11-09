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

	protected:
		virtual std::string GetType() const { return "NULL"; }
		virtual void Serialize(const void* obj, SerializationBufferWrite& buffer) const = 0;
		virtual void Deserialize(void* obj, const SerializationBufferRead& buffer) const = 0;
	};

	template<typename T>
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
			T* t = new T();
			Serialization::GetSerializableObjects().emplace(t->GetType(), t);
			return true;
		}
	};

	template<class T>
	bool Serializable<T>::reg = Serializable<T>::Init();

	class Serialization
	{
	public:
		static void SaveAsset(Object* obj);
		static void SerializeObject(SerializationBufferWrite& buffer, Object* obj, const Class* cl, std::string path = "", std::string prefix = "");
		static bool SerializeProperty(SerializationBufferWrite& buffer, Object* obj, const std::string& path, const std::pair<std::string, ClassProperty>& prop);

		static void LoadAsset(std::string path);
		static void LoadAsset(SerializationBufferRead& buffer);

		static std::unordered_map<std::string, SerializableBase*>& GetSerializableObjects()
		{
			static std::unordered_map<std::string, SerializableBase*> so;
			return so;
		}
	};

	// primitive types
	struct SerializableInt : Serializable<SerializableInt>
	{
		virtual std::string GetType() const { return "int"; }
		virtual void Serialize(const void* obj, SerializationBufferWrite& buffer) const override
		{
			buffer.Write(std::to_string(*reinterpret_cast<const int*>(obj)));
		}
		virtual void Deserialize(void* obj, const SerializationBufferRead& buffer) const override
		{

		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableInt)

	struct SerializableFloat : Serializable<SerializableFloat>
	{
		virtual std::string GetType() const { return "float"; }
		virtual void Serialize(const void* obj, SerializationBufferWrite& buffer) const override
		{
			buffer.Write(std::to_string(*reinterpret_cast<const float*>(obj)));
		}
		virtual void Deserialize(void* obj, const SerializationBufferRead& buffer) const override
		{

		}
	};
	DEFINE_SERIALIZABLE_OBJECT(SerializableFloat)
}