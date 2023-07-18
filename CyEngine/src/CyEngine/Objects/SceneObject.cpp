#include "cypch.h"
#include "SceneObject.h"

namespace Cy
{
    void SceneObject::Tick()
    {

    }

    void SceneObject::AddComponent(Component* component)
    {
        component->SetParent(this);
        m_Components.push_back(component);
    }
}
