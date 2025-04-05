#pragma once

#include <unordered_map>
#include "GUID.h"

namespace Cy
{
	class Object;

	class ObjectManager
	{
	public:
		static ObjectManager* Get();
		
		// TODO: non-templated object spawning
		// TODO: passing classes into object spawn functions

		template<typename T>
		static T* CreateObject() 
		{
			T* t = new T();
			return t;
		}

		static void DestroyObject(Object* obj);
		template<typename T>
		static SharedPtr<T> GetSharedObjectPtrTyped(T* obj)
		{
			return *reinterpret_cast<SharedPtr<T>*>(&GetSharedObjectPtr(obj));
		}
		static SharedPtr<Object> GetSharedObjectPtr(Object* obj);

		static SharedPtr<Object> FindObject(const guid& guid) { return (*Get()->ObjectMap.find(guid)).second; }

		void RegisterObject(Object* obj, guid _guid = guid());
		
	private:
		static ObjectManager* Instance;

		std::unordered_map<guid, SharedPtr<Object>> ObjectMap;
	};
}
