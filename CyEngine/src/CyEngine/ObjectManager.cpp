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

    void ObjectManager::DestroyObject(Object* obj)
    {
        obj->End();
        Get()->ObjectMap.erase(obj->ObjectGUID);
    }

    SharedPtr<Object> ObjectManager::GetSharedPtr(Object* obj)
    {
        return Get()->ObjectMap[obj->ObjectGUID];
    }

    void ObjectManager::RegisterObject(Object* obj)
    {
        guid guid = guid::Make();
        ObjectMap.emplace(guid, SharedPtr(obj));
        obj->ObjectGUID = guid;
    }
}

