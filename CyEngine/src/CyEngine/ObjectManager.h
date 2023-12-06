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
		static SharedPtr<T> GetSharedPtrTyped(T* obj)
		{
			return *reinterpret_cast<SharedPtr<T>*>(&GetSharedPtr(obj));
		}
		static SharedPtr<Object> GetSharedPtr(Object* obj);

		static SharedPtr<Object> FindObject(const guid& guid) { return (*Get()->ObjectMap.find(guid)).second; }

		void RegisterObject(Object* obj);

	private:
		static ObjectManager* Instance;

		std::unordered_map<guid, SharedPtr<Object>> ObjectMap;
	};
}
