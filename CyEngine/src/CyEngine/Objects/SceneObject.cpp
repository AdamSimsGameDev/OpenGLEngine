#include "cypch.h"
#include "SceneObject.h"
#include "CyEngine/Components/Component.h"

namespace Cy
{
    void SceneObject::Tick(float deltaTime)
    {

    }

    void SceneObject::AddComponent(Component* component)
    {
        component->SetParent(this);
        m_Components.Add(component);
    }
}
