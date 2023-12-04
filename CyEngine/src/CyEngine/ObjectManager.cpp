#include "cypch.h"
#include "ObjectManager.h"
#include "Objects/Object.h"

namespace Cy
{
    ObjectManager* ObjectManager::Instance = nullptr;

    ObjectManager* ObjectManager::Get()
    {
        if (Instance == nullptr)
        {
            Instance = new ObjectManager();
        }
        return Instance;
    }

    void ObjectManager::RegisterObject(Object* obj)
    {
        ObjectMap.emplace(GUID::Make(), SharedPtr(obj));
    }
}

