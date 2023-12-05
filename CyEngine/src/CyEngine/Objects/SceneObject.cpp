#include "cypch.h"
#include "SceneObject.h"
#include "CyEngine/Components/Component.h"
#include "CyEngine/Scene.h"

namespace Cy
{
    void SceneObject::Destroy()
    {
        for (auto& component : m_Components)
        {
            component->Destroy();
        }
        GetScene()->DestroyObject(this);
    }

    void SceneObject::Tick(float deltaTime)
    {
        for (auto& component : m_Components)
        {
            component->Tick(deltaTime);
        }
    }

    void SceneObject::AddComponent(Component* component)
    {
        component->SetParent(this);
        m_Components.Add(component);
    }
}
