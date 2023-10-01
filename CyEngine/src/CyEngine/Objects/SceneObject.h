#pragma once
#include "CyEngine/Transform.h"
#include "Object.h"
#include "generated/SceneObject.gen.h"

namespace Cy
{
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

		PROPERTY()
		Transform m_Transform;
		
		PROPERTY()
		std::vector<Component*> m_Components;
	};
}
