#include "cypch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ringbuffer_sink.h"

namespace Cy
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> Log::s_InternalBuffer;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_InternalBuffer = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(128);

		s_CoreLogger = spdlog::stdout_color_mt("ENG");
		s_CoreLogger->sinks().push_back(s_InternalBuffer);
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->sinks().push_back(s_InternalBuffer);
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	std::vector<std::string> Log::GetLast(int count)
	{
		return s_InternalBuffer->last_formatted(128);
	}

	void Log::Clear()
	{
		s_InternalBuffer->flush();
	}
}
