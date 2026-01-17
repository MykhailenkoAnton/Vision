#pragma once

#include <string>
#include <string_view>
#include <format>
#include <memory>
#include <source_location>
#include <concepts>
#include "Core/Utility.h"

namespace Vision
{
    enum class LogVerbosity : uint8_t
    {
        NoLogging = 0,
        Display,
        Warning,
        Error,
        Log,
        Fatal
    };

    struct LogCategory
    {
        explicit LogCategory(const std::string& name) : m_name(name) {}
        std::string name() const { return m_name; }

    private:
        const std::string m_name;
    };

    class Log final : public NoCopyable
    {
    public:
        static Log& getInstance()
        {
            static Log instance;
            return instance;
        }

        // Using direct call is unsafe! Don't do it!
        void log(const LogCategory& category, LogVerbosity verbosity, const std::string& message, bool bShowLocation = false,
            const std::source_location location = std::source_location::current()) const;

    private:
        Log();
        ~Log();

    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };

    constexpr LogVerbosity c_minLogVerbocity = LogVerbosity::Display;
    constexpr LogVerbosity c_maxLogVerbocity = LogVerbosity::Fatal;

    // concepts
    template <typename T>
    concept ValidLogCategory = std::constructible_from<LogCategory, T>;

    template <typename T>
    concept LoggableMessage = std::convertible_to<T, std::string> || std::convertible_to<T, std::string_view>;

    template <LogVerbosity V>
    concept ValidVerbocityLevel = V == LogVerbosity::NoLogging || V == LogVerbosity::Display || V == LogVerbosity::Warning ||
                                  V == LogVerbosity::Error || V == LogVerbosity::Fatal || V == LogVerbosity::Log;

}  // namespace Vision

//
#define DEFINE_LOG_CATEGORY_STATIC(logName)          \
    namespace                                        \
    {                                                \
        const Vision::LogCategory logName(#logName); \
    }

#define VI_LOG_IMPL(categoryName, verbosity, showLocation, formatStr, ...)                                                                 \
    do                                                                                                                                     \
    {                                                                                                                                      \
        if constexpr (Vision::LogVerbosity::verbosity >= Vision::c_minLogVerbocity &&                                                      \
                      Vision::LogVerbosity::verbosity <= Vision::c_maxLogVerbocity)                                                        \
        {                                                                                                                                  \
            static_assert(Vision::ValidVerbocityLevel<Vision::LogVerbosity::verbosity>,                                                    \
                "Verbocity must be one of NoLogging, Display, Warning, Error, Fatal, Log");                                                \
            static_assert(Vision::ValidLogCategory<decltype(categoryName)>, "Category must be of type LogCategory");                       \
            static_assert(Vision::LoggableMessage<decltype(formatStr)>, "Message must be convertible to std::string or std::string_view"); \
            Vision::Log::getInstance().log(                                                                                                \
                categoryName, Vision::LogVerbosity::verbosity, std::format(formatStr __VA_OPT__(, ) __VA_ARGS__), showLocation);           \
        }                                                                                                                                  \
    } while (0)

#define VI_LOG(categoryName, verbosity, formatStr, ...) VI_LOG_IMPL(categoryName, verbosity, false, formatStr, __VA_ARGS__)

#define VI_LOG_DEBUG(categoryName, verbosity, formatStr, ...) VI_LOG_IMPL(categoryName, verbosity, true, formatStr, __VA_ARGS__)