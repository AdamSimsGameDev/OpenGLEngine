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