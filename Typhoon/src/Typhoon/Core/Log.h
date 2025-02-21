#pragma once

#include "Typhoon/Core/Base.h"

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Typhoon {

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
	};

}

// Core log macros
#define TY_TRACE(...)    ::Typhoon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TY_INFO(...)     ::Typhoon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TY_WARN(...)     ::Typhoon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TY_ERROR(...)    ::Typhoon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TY_CRITICAL(...) ::Typhoon::Log::GetCoreLogger()->critical(__VA_ARGS__)