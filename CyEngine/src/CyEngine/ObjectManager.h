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
			Get()->RegisterObject(t);
			return t;
		}

	private:
		void RegisterObject(Object* obj);

	private:
		static ObjectManager* Instance;

		std::unordered_map<GUID, SharedPtr<Object>> ObjectMap;
	};
}
