#include "cypch.h"
#include "Object.h"
#include "CyEngine/ObjectManager.h"

namespace Cy
{
	Object::Object()
		: m_Parent(nullptr)
	{
		ObjectManager::Get()->RegisterObject(this);
	}

	void Object::Start()
	{
		// Stub
	}

	void Object::End()
	{
		// Stub
	}

	void Object::Destroy()
	{
		ObjectManager::DestroyObject(this);
	}

	void Object::SetParent(Object* parent)
	{
		m_Parent = parent;
	}

	const guid& Object::GetGUID() const
	{
		return ObjectGUID;
	}
}
