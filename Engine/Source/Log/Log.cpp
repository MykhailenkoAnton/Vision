#include "Log.h"

#include <memory>
#include <unordered_map>
#include <filesystem>
#include <chrono>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Vision
{
    namespace fs = std::filesystem;

    namespace
    {
        const std::unordered_map<LogVerbosity, spdlog::level::level_enum> c_vervosityMap = {
            {LogVerbosity::NoLogging, spdlog::level::off},  //
            {LogVerbosity::Display, spdlog::level::info},   //
            {LogVerbosity::Warning, spdlog::level::warn},   //
            {LogVerbosity::Error, spdlog::level::err},      //
            {LogVerbosity::Log, spdlog::level::info},       //
            {LogVerbosity::Fatal, spdlog::level::critical}  //
        };

        constexpr const char* c_logPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
        constexpr const char* c_logFilePrefix = "Vision";
        constexpr const char* c_logFileExtension = "txt";
        constexpr const char* c_timestampFormat = "{:%Y.%d.%m-%H.%M.%S}";
        const fs::path c_logDirectory = "logs";
    }  // namespace

    // pImpl
    class Log::Impl
    {
    public:
        Impl()
        {
            const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            m_consoleLogger = std::make_unique<spdlog::logger>("console", consoleSink);
            m_consoleLogger->set_pattern(c_logPattern);

            const auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(makeLogFile().string(), true);
            m_fileLogger = std::make_unique<spdlog::logger>("file", fileSink);
            m_fileLogger->set_pattern(c_logPattern);
        }

        void log(LogVerbosity verbosity, const std::string& message) const
        {
            const auto spdLevel = c_vervosityMap.at(verbosity);

            if (verbosity != LogVerbosity::Log && m_consoleLogger->should_log(spdLevel))
            {
                m_consoleLogger->log(spdLevel, message);
            }

            if (m_fileLogger->should_log(spdLevel))
            {
                m_fileLogger->log(spdLevel, message);
            }

            if (verbosity == LogVerbosity::Fatal)
            {
                PLATFORM_BREAK();
            }
        }

    private:
        std::unique_ptr<spdlog::logger> m_consoleLogger;
        std::unique_ptr<spdlog::logger> m_fileLogger;

        fs::path makeLogFile() const
        {
            fs::create_directory(c_logDirectory);
            const auto now = std::chrono::system_clock::now();
            const auto now_seconds = std::chrono::floor<std::chrono::seconds>(now);
            const std::string timestamp = std::format(c_timestampFormat, now_seconds);
            const std::string logName = std::format("{}-{}.{}", c_logFilePrefix, timestamp, c_logFileExtension);
            return c_logDirectory / logName;
        }
    };

    // interface
    Log::Log() : m_pImpl(std::make_unique<Impl>()) {}
    Log::~Log() = default;

    void Log::log(const LogCategory& category, LogVerbosity verbosity, const std::string& message, bool bShowLocation,
        const std::source_location location) const
    {
        const std::string fmtMsg = bShowLocation
                                       ? std::format("[{}] [{}:{}] {}", category.name(), location.file_name(), location.line(), message)
                                       : std::format("[{}] {}", category.name(), message);

        m_pImpl->log(verbosity, fmtMsg);
    }
}  // namespace Vision
