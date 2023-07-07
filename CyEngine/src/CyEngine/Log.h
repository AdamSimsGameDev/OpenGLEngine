#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Cy
{
	class CY_API Log
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

// Core logging macros
#define CY_CORE_TRACE(...) ::Cy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CY_CORE_INFO(...)  ::Cy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CY_CORE_WARN(...)  ::Cy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CY_CORE_ERROR(...) ::Cy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CY_CORE_FATAL(...) ::Cy::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client logging macros
#define CY_TRACE(...) ::Cy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CY_INFO(...)  ::Cy::Log::GetClientLogger()->info(__VA_ARGS__)
#define CY_WARN(...)  ::Cy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CY_ERROR(...) ::Cy::Log::GetClientLogger()->error(__VA_ARGS__)
#define CY_FATAL(...) ::Cy::Log::GetClientLogger()->fatal(__VA_ARGS__)
