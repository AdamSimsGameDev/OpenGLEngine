#pragma once

#include "CyEngine/Core.h"
#include "CyEngine/GUID.h"
#include "generated/Object.gen.h"

namespace Cy
{
	CLASS()
	class Object
	{
		friend class ObjectManager;

		GENERATED_CLASS(Object);

	public:
		Object();

		virtual void Start();
		virtual void End();

		virtual void Destroy();

		virtual void SetParent(Object* parent);
		
		template<typename ObjectType>
		ObjectType* GetParent() const { return Cast<ObjectType>(m_Parent); }
		template<typename ObjectType>
		ObjectType* GetParentChecked() const { return CastChecked<ObjectType>(m_Parent); }

		const guid& GetGUID() const;

	private:
		Object* m_Parent;
		guid ObjectGUID;
	};
}
