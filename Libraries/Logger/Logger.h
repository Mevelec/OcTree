#pragma once
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Logger
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

#define INIT(...) ::Logger::Log::Init();
// Core log macros
#define CORE_TRACE(...) ::Logger::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CORE_INFO(...)  ::Logger::Log::GetCoreLogger()->info(__VA_ARGS__);
#define CORE_WARN(...)  ::Logger::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CORE_ERROR(...) ::Logger::Log::GetCoreLogger()->error(__VA_ARGS__);
#define CORE_FATAL(...) ::Logger::Log::GetCoreLogger()->critical(__VA_ARGS__);

// Client log macros
#define TRACE(...) ::Logger::Log::GetClientLogger()->trace(__VA_ARGS__);
#define INFO(...)  ::Logger::Log::GetClientLogger()->info(__VA_ARGS__);
#define WARN(...)  ::Logger::Log::GetClientLogger()->warn(__VA_ARGS__);
#define ERROR(...) ::Logger::Log::GetClientLogger()->error(__VA_ARGS__);
#define FATAL(...) ::Logger::Log::GetClientLogger()->critical(__VA_ARGS__);
