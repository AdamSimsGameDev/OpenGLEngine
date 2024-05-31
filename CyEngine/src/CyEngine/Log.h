#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/sinks/ringbuffer_sink.h>

namespace Cy
{
	class CY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		static std::vector<std::string> GetLast(int count);
		static void Clear();
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		static std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> s_InternalBuffer;
	};
}

// Core logging macros
#define CY_CORE_TRACE(...) ::Cy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CY_CORE_LOG(...)  ::Cy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CY_CORE_WARN(...)  ::Cy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CY_CORE_ERROR(...) ::Cy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CY_CORE_FATAL(...) ::Cy::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client logging macros
#define CY_TRACE(...) ::Cy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CY_LOG(...)  ::Cy::Log::GetClientLogger()->info(__VA_ARGS__)
#define CY_WARN(...)  ::Cy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CY_ERROR(...) ::Cy::Log::GetClientLogger()->error(__VA_ARGS__)
#define CY_FATAL(...) ::Cy::Log::GetClientLogger()->critical(__VA_ARGS__)

// Assert macros
#define CY_CORE_ASSERT(condition, ...)	if (!(condition)) ::Cy::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define CY_ASSERT(condition, ...)		if (!(condition)) ::Cy::Log::GetClientLogger()->critical(__VA_ARGS__);
