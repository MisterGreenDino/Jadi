#pragma once

#ifdef JADI_PLATFORM_WINDOWS
	#ifdef JADI_BUILD_DLL
		#define JADI_API __declspec(dllexport)
	#else
		#define JADI_API __declspec(dllimport)
	#endif
#else
	#error Jadi only support windows !
#endif