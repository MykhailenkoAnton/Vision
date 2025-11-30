#include "Engine.h"
#include "Log/Log.h"
#include <format>

namespace Vision
{
    Engine::Engine()
    {
        Log::getInstance().log(Vision::LogVerbosity::Display, std::format("Hello from Vision Engine! Version: {}", version()));

        Log::getInstance().log(Vision::LogVerbosity::NoLogging, "NoLogging example log");
        Log::getInstance().log(Vision::LogVerbosity::Warning, "Warning example log");
        Log::getInstance().log(Vision::LogVerbosity::Error, "Error example log");
        Log::getInstance().log(Vision::LogVerbosity::Fatal, "Critical example log");
    }
}  // namespace Vision
