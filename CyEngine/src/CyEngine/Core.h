#pragma once

#ifdef CY_PLATFORM_WINDOWS
	#if CY_DYNAMIC_LINK
		#ifdef CY_BUILD_DLL
			#define CY_API __declspec(dllexport)
		#else
			#define CY_API __declspec(dllimport)
		#endif
	#else
		#define CY_API
	#endif
#else
	#error Only windows supported at present
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)
#define BIND_EVENT_FUNC_STATIC(x) std::bind(&x)

template<typename To, typename From>
static To* Cast(From* from)
{
	if (from)
	{
		if (auto cast = static_cast<To*>(from))
		{
			return cast;
		}
	}
	return nullptr;
}

#define GET_NAME(x) typeid(x).name()
#define GET_NAME_SAFE(x) x ? typeid(x).name() : "NULL"

template<typename To, typename From>
static To* CastChecked(From* from)
{
	auto cast = Cast<To>(from);
	//CY_CORE_ASSERT(cast, "CastChecked failed, {0} cannot be cast to type {1}. ", GET_NAME_SAFE(cast), typeid(from).name());
	return cast;
}

#define __CLASS__ 

#define CLASS(...)
#define STRUCT(...)
#define PROPERTY(...)
#define GENERATED_CLASS(type) public:\
	friend class type##Class;\
	static class Class* GetStaticClass() { return type##Class::Get(); }\
	virtual class Class* GetClass() const { return type##::GetStaticClass(); }

#include "CyEngine/Class.h"
#include "CyEngine/String.h"

// Maths
#include "CyEngine/Maths/Colour.h"
#include "CyEngine/Maths/Maths.h"
#include "CyEngine/Maths/Matrix.h"
#include "CyEngine/Maths/Quat.h"
#include "CyEngine/Maths/Vector.h"

#include "CyEngine/Log.h"

// Input
#include "CyEngine/Input.h"
#include "CyEngine/KeyCode.h"
