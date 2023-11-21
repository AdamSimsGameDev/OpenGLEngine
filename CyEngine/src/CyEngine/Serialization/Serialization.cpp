#include "cypch.h"
#include "Serialization.h"
#include "CyEngine/Objects/Object.h"
#include "CyEngine/Transform.h"
#include <fstream>

namespace Cy
{
	const SerializableBase* Serialization::FindSerializableProperty(std::string type)
	{
		const auto& cont = Serialization::GetSerializableObjects();
		const auto& found = cont.find(type);
		if (found != cont.end())
		{
			return found->second;
		}
		return nullptr;
	}
}
