#pragma once
#include "CyEngine/Core.h"
#include "Object.h"
#include "CyEngine/Transform.h"
#include "generated/SceneObject.gen.h"

namespace Cy
{
	class Component;

	CLASS()
	class SceneObject : public Object
	{
		GENERATED_CLASS(SceneObject)

	public:
		SceneObject() : Object(), m_Transform() { }

		virtual void Tick(float deltaTime);

		const Transform& GetTransform() const { return m_Transform; }
		Transform& GetTransform() { return m_Transform; }

		template<typename ComponentType>
		ComponentType* CreateAndAddComponent()
		{
			ComponentType* t = new ComponentType();
			AddComponent(t);
			t->Start();
			return t;
		}
		void AddComponent(Component* component);

		PROPERTY(Tooltip="Testing a string with spaces (and brackets), oh and commas too")
		String Name;

		PROPERTY()
		Transform m_Transform;
		
		std::vector<Component*> m_Components;
	};
}
