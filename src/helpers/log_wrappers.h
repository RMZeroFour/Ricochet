#pragma once

#include "buildinfo.h"

#include <spdlog/common.h>

#define SOURCE_LOC spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }

#define LOG_DEBUG(logger, ...)                                          \
	do                                                                  \
	{                                                                   \
		if (Ricochet_ENABLE_DEBUG_LOGGING)                              \
		{                                                               \
			logger->log(SOURCE_LOC, spdlog::level::debug, __VA_ARGS__); \
		}                                                               \
	} while (false)
	
#define LOG_INFO(logger, ...)                                      \
	do                                                             \
	{                                                              \
		logger->log(SOURCE_LOC, spdlog::level::info, __VA_ARGS__); \
	} while (false)
	
#define LOG_WARN(logger, ...)                                      \
	do                                                             \
	{                                                              \
		logger->log(SOURCE_LOC, spdlog::level::warn, __VA_ARGS__); \
	} while (false)

#define LOG_ERROR(logger, ...)                                    \
	do                                                            \
	{                                                             \
		logger->log(SOURCE_LOC, spdlog::level::err, __VA_ARGS__); \
	} while (false)
