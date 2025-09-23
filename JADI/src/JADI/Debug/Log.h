#pragma once

#include <memory>

#include "../Core/Core.h"
#include "spdlog/spdlog.h"

namespace JADI {
	class JADI_API Log
	{

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

// Core log macros : Arranged by severity
#define LOG_CORE_TRACE(...)    ::JADI::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)	    ::JADI::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)	    ::JADI::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)    ::JADI::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...)	::JADI::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros : Arranged by severity
#define LOG_APP_TRACE(...)         ::JADI::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_APP_INFO(...)          ::JADI::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_APP_WARN(...)	        ::JADI::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_APP_ERROR(...)         ::JADI::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_APP_FATAL(...)         ::JADI::Log::GetClientLogger()->critical(__VA_ARGS__)

