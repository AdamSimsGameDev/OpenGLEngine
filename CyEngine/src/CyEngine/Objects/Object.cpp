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

	// Object duplication should work as so:
	// - Create a new object of the same type (this should be done before-hand).
	// - During duplication, store a map of duplicated GUIDs (so that we know what has changed, from and to what)
	// - Copy over all properties from one object to another, shallow copying them.
	// - Once the above has been done for all objects, re-iterate through the object properties, if the property references an Object that
	//	 has a GUID in the copied array, replace it with the new object.

	void Object::CopyFrom(const Object* obj)
	{
		ObjectCopyState state;
		CopyFrom(state, obj);
		UpdateReferencesFrom(state);
	}

	void Object::CopyFrom(ObjectCopyState& state, const Object* obj)
	{
		// add the GUID copy to the state
		state.AddGUID(obj, this);
		
		// shallow copy each of the properties.
		for (const auto& prop : GetClass()->Properties)
		{
			prop.second.Setter(this, prop.second.Getter(obj));
		}
	}

	void Object::UpdateReferencesFrom(const ObjectCopyState& state)
	{
		for (const auto& prop : GetClass()->Properties)
		{
			const Class* cl = Class::GetClassFromName(prop.second.Type);
			if (cl && cl->IsChildOf<Object>())
			{ 
				Object* obj = *reinterpret_cast<Object**>(prop.second.Getter(this));
				if (state.IsCopied(obj->GetGUID()))
				{
					prop.second.Setter(this, ObjectManager::FindObject(state.GetCopiedGUID(obj->GetGUID())).Get());
				}
			}
		}
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
		if ( parent && parent->GetParent<Object>() == this )
		{
			parent->SetParent( nullptr );
		}
		m_Parent = parent;
	}

	const guid& Object::GetGUID() const
	{
		return ObjectGUID;
	}

	void ObjectCopyState::AddGUID(const Object* from, const Object* to)
	{
		CopiedGUIDs.emplace(from->GetGUID(), to->GetGUID());
	}
}
