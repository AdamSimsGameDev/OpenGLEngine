#pragma once

#ifdef CY_PLATFORM_WINDOWS
	#ifdef CY_BUILD_DLL
		#define CY_API __declspec(dllexport)
	#else
		#define CY_API __declspec(dllimport)
	#endif
#else
	#error Only windows supported at present
#endif

#define BIT(x) (1 << x)