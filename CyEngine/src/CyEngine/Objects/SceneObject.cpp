#include "cypch.h"
#include "SceneObject.h"
#include "CyEngine/Components/Component.h"
#include "CyEngine/World.h"

namespace Cy
{
    void SceneObject::Destroy()
    {
        for (auto& component : m_Components)
        {
            component->Destroy();
        }
        GetWorld()->DestroyObject(this);
    }

    void SceneObject::Tick(float deltaTime)
    {
        for (auto& component : m_Components)
        {
            component->Tick(deltaTime);
        }
    }

    void SceneObject::SetParent(Object* parent)
    {
        if (SceneObject* so = GetParent<SceneObject>())
        {
            so->m_Children.Remove(this);
        }

        Object::SetParent(parent);

        if (SceneObject* so = GetParent<SceneObject>())
        {
            so->m_Children.Add(this);
        }
    }

    void SceneObject::AddComponent(Component* component)
    {
        component->SetParent(this);
        m_Components.Add(component);
    }
}
