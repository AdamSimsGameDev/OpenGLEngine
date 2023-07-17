#pragma once
#include "CyEngine/Transform.h"
#include "Object.h"

namespace Cy
{
	class SceneObject : public Object
	{
	public:
		SceneObject() : Object(), m_Transform() { }

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

		virtual std::string ClassName() const override { return "SceneObject"; }

	private:
		Transform m_Transform;
		std::vector<Component*> m_Components;
	};
}
