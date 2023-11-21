#include "cypch.h"
#include "Serialization.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Transform.h"
#include <fstream>

namespace Cy
{
	void Serialization::SaveAsset(Object* obj)
	{
		SerializationBufferWrite buffer("test.asset");
		SerializeObject(buffer, obj, obj->GetClass());
		buffer.Close();
	}
	void Serialization::SerializeObject(SerializationBufferWrite& buffer, Object* obj, const Class* cl, std::string path, std::string prefix)
	{
		for (const auto& prop : cl->Properties)
		{
			buffer.Write(prefix + "\"" + prop.first + "\":");
			if (SerializeProperty(buffer, obj, path + prop.first, prop))
			{
				continue;
			}
			buffer.Write("\n");
			// see if the property itself is a class
			const Class* ncl = Class::GetClassFromName(prop.second.Type);
			if (ncl)
			{
				SerializeObject(buffer, obj, ncl, path + prop.first + "|", prefix + "\t");
			}
		}
	}

	bool Serialization::SerializeProperty(SerializationBufferWrite& buffer, Object* obj, const std::string& path, const std::pair<std::string, ClassProperty>& prop)
	{
		const Class* cl = obj->GetClass();
		for (const auto& so : Serialization::GetSerializableObjects())
		{
			if (so.first != prop.second.Type)
				continue;
			void* data = cl->GetPropertyValuePtrFromName(path, prop.second.Type, obj);
			so.second->Serialize(data, buffer);
			buffer.Write("\n");
			return true;
		}
		return false;
	}

	void Serialization::LoadAsset(std::string path)
	{
		SerializationBufferRead buffer(path);
		LoadAsset(buffer);
	}

	void Serialization::LoadAsset(SerializationBufferRead& buffer)
	{

	}
}
