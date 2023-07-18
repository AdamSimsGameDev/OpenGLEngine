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
		if (auto cast = dynamic_cast<To*>(from))
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
	// CY_CORE_ASSERT(cast, "CastChecked failed, {0} cannot be cast to type {1}. ", GET_NAME_SAFE(cast), typeid(from).name());
	return cast;
}

#define __CLASS__ 
