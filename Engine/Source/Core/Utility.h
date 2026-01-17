#pragma once

namespace Vision
{
    class NoCopyable
    {
    protected:
        NoCopyable() = default;
        ~NoCopyable() = default;

        NoCopyable(const NoCopyable&) = delete;
        NoCopyable& operator=(const NoCopyable&) = delete;

        NoCopyable(NoCopyable&&) = delete;
        NoCopyable& operator=(NoCopyable&&) = delete;
    };

}  // namespace Vision

#if defined(_MSC_VER)
#define PLATFORM_BREAK() __debugbreak()
#else
#include <signal.h>
#define PLATFORM_BREAK() raise(SIGTRAP)
#endif