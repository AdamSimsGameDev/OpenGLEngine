#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/GUID.h"
#include "generated/Object.gen.h"

namespace Cy
{
	class Object;

	struct ObjectCopyState
	{
		std::unordered_map<guid, guid> CopiedGUIDs;
	
		void AddGUID(const Object* from, const Object* to);
		bool IsCopied(const guid& guid) const { return CopiedGUIDs.find(guid) != CopiedGUIDs.end(); }
		const guid& GetCopiedGUID(const guid& guid) const { return (*CopiedGUIDs.find(guid)).second; }
	};

	CLASS()
	class Object
	{
		friend class ObjectManager;

		GENERATED_CLASS(Object);

	public:
		Object();

		void CopyFrom(const Object* obj);
		virtual void CopyFrom(ObjectCopyState& state, const Object* obj);
		virtual void UpdateReferencesFrom(const ObjectCopyState& state);

		virtual void Start();
		virtual void End();

		virtual void Destroy();

		virtual void SetParent(Object* parent);
		
		template<typename ObjectType>
		ObjectType* GetParent() const { return Cast<ObjectType>(m_Parent); }
		template<typename ObjectType>
		ObjectType* GetParentChecked() const { return CastChecked<ObjectType>(m_Parent); }

		const guid& GetGUID() const;

		const String& GetName() const { return Name; }
		void SetName(const String& Name) { this->Name = Name; }

	private:
		PROPERTY()
		String Name;

		PROPERTY(Hidden)
		Object* m_Parent;

		guid ObjectGUID;
	};
}
