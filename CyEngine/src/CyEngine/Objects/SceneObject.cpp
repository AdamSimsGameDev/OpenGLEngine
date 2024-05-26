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
            m_Transform->SetParent(so->m_Transform, true);
        }
        else
        {
            m_Transform->SetParent(nullptr, true);
        }
    }

    void SceneObject::CopyFrom(ObjectCopyState& state, const Object* obj)
    {
        Object::CopyFrom(state, obj);

        const SceneObject* _obj = Cast<SceneObject>(obj);
        for (const auto& comp : _obj->m_Components)
        {
            if (comp == _obj->m_Transform)
                continue;
            Component* nc = comp->GetClass()->New<Component>();
            nc->CopyFrom(comp);
            AddComponent(nc);
        }
        for (const auto& _so : _obj->m_Children)
        {
            SceneObject* so = GetWorld()->CreateSceneObject<SceneObject>(Vector3::Zero, Quat::Identity);
            so->CopyFrom(state, _so);
            so->SetParent(this);
        }
    }

    void SceneObject::UpdateReferencesFrom(const ObjectCopyState& state)
    {
        Object::UpdateReferencesFrom(state);

        for (auto& comp : m_Components)
        {
            comp->UpdateReferencesFrom(state);
            comp->Start();
        }
    }

#if CY_EDITOR
    void SceneObject::EditorTick(float deltaTime)
    {
        for (auto& component : m_Components)
        {
            component->EditorTick(deltaTime);
        }
    }
#endif

    Component* SceneObject::CreateAndAddComponent(const Class* cl)
    {
        Component* t = cl->New<Component>();
        AddComponent(t);
        t->Start();
        return t;
    }

    void SceneObject::AddComponent(Component* component)
    {
        component->SetParent(this);
        m_Components.Add(component);
    }

    void SceneObject::RemoveComponent(Component* component)
    {
        if (component->GetParent<SceneObject>() != this)
        {
            return;
        }
        component->SetParent(nullptr);
        m_Components.Remove(component);
    }
}
