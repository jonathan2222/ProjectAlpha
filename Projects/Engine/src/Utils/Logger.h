#ifndef PA_LOGGER_H
#define PA_LOGGER_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#ifdef PA_DEBUG
	#define PA_LOG_INIT() \
			spdlog::set_level(spdlog::level::info); \
			spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] [%s:%#] %v");

	#define PA_LOG_INFO(...) SPDLOG_INFO(__VA_ARGS__)
	#define PA_LOG_WARN(...) SPDLOG_WARN(__VA_ARGS__)
	#define PA_LOG_ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
	#define PA_LOG_CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)
	#define PA_LOG_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#else
	#define PA_LOG_INIT()

	#define PA_LOG_INFO(...)
	#define PA_LOG_WARN(...)
	#define PA_LOG_ERROR(...)
	#define PA_LOG_CRITICAL(...)
	#define PA_LOG_DEBUG(...)
#endif

#endif
