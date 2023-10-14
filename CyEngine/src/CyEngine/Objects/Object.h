#pragma once

#include "CyEngine/Core.h"
#include "generated/Object.gen.h"

namespace Cy
{
	CLASS()
	class Object
	{
		GENERATED_CLASS(Object);

	public:
		Object() : m_Parent(nullptr) { }

		virtual void Start();
		virtual void End();

		virtual void SetParent(Object* parent);
		
		template<typename ObjectType>
		ObjectType* GetParent() const { return Cast<ObjectType>(m_Parent); }
		template<typename ObjectType>
		ObjectType* GetParentChecked() const { return CastChecked<ObjectType>(m_Parent); }

	private:
		Object* m_Parent;
	};
}
