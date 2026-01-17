#include "Engine.h"
#include "Log/Log.h"
#include <format>

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

namespace Vision
{

    Engine::Engine()
    {

        // Log::getInstance().log(LogEngine, Vision::LogVerbosity::Display, std::format("Hello from Vision Engine! Version: {}",
        // version()));

        // Log::getInstance().log(LogEngine, Vision::LogVerbosity::NoLogging, "NoLogging example log", true);
        // Log::getInstance().log(LogEngine, Vision::LogVerbosity::Warning, "Warning example log", true);
        // Log::getInstance().log(LogEngine, Vision::LogVerbosity::Error, "Error example log", true);
        // Log::getInstance().log(LogEngine, Vision::LogVerbosity::Log, "File example log");
        //  Log::getInstance().log(LogEngine, Vision::LogVerbosity::Fatal, "Critical example log");

        //
        VI_LOG(LogEngine, Display, "Hello from Vision Engine! Version: {}", version());
        VI_LOG(LogEngine, NoLogging, "NoLogging example log");
        VI_LOG_DEBUG(LogEngine, Warning, "Warning example log");
        VI_LOG_DEBUG(LogEngine, Error, "Error example log");
        VI_LOG(LogEngine, Fatal, "Critical example log");

        VI_LOG(LogEngine, Log, "File example log");
    }
}  // namespace Vision
