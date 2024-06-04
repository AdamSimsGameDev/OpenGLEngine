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

#define CY_EDITOR 1

#include "CyEngine/Log.h"

template <typename Target, typename Source>
inline Target* Cast(Source* x)
{
	Target* tmp = dynamic_cast<Target*>(x);
	if (tmp == nullptr) return nullptr;
	return tmp;
}

template <typename Target, typename Source>
inline const Target* Cast(const Source* x)
{
	const Target* tmp = dynamic_cast<const Target*>(x);
	if (tmp == nullptr) return nullptr;
	return tmp;
}

#define GET_NAME(x) typeid(x).name()
#define GET_NAME_SAFE(x) x ? typeid(x).name() : "NULL"

template<typename To, typename From>
static To* CastChecked(From* from)
{
	auto cast = Cast<To>(from);
	CY_CORE_ASSERT(cast, "CastChecked failed, {0} cannot be cast to type {1}. ", GET_NAME_SAFE(cast), typeid(from).name());
	return cast;
}

#define __CLASS__ 

#define CLASS(...)
#define ENUM(...)
#define STRUCT(...)
#define PROPERTY(...)
#define GENERATED_CLASS(type) public:\
	friend class type##Class;\
	static class Class* GetStaticClass() { return type##Class::Get(); }\
	virtual class Class* GetClass() const { return type##::GetStaticClass(); }\
	bool IsClassDefaultObject() const { return type##::GetStaticClass()->GetClassDefaultObject<type##>() == this; }

static int SizeTToInt(size_t data)
{
	if (data > std::numeric_limits<int>::max())
		throw std::exception("Invalid cast.");
	return static_cast<int>(data);
}

template<typename T>
static T* New()
{
	return T::GetStaticClass()->New<T>();
}

#include "CyEngine/SmartPointer.h"
#include "CyEngine/Array.h"
#include "CyEngine/Class.h"
#include "CyEngine/String.h"

// Maths
#include "CyEngine/Maths/Colour.h"
#include "CyEngine/Maths/Maths.h"
#include "CyEngine/Maths/Matrix.h"
#include "CyEngine/Maths/Quat.h"
#include "CyEngine/Maths/Vector.h"

// Input
#include "CyEngine/Input.h"
#include "CyEngine/KeyCode.h"
