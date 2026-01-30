#include "Log/Log.h"
#include <gtest/gtest.h>

using namespace Vision;

TEST(LogConceptsTest, LogCategoryNameShouldBeValid)
{
    LogCategory category1("TestCategory1");
    EXPECT_EQ(category1.name(), "TestCategory1");

    LogCategory category2("TestCategory2");
    EXPECT_EQ(category2.name(), "TestCategory2");

    EXPECT_NE(category1.name(), category2.name());
}

TEST(LogConceptsTest, LogCategoryTypeShouldBeValid)
{
    static_assert(ValidLogCategory<LogCategory>);
    static_assert(ValidLogCategory<const LogCategory&>);
}

TEST(LogConceptsTest, LogMessageMessageShouldBeValid)
{
    static_assert(LoggableMessage<std::string>);
    static_assert(LoggableMessage<const std::string&>);
    static_assert(LoggableMessage<std::string_view>);
    static_assert(LoggableMessage<const std::string_view&>);
    static_assert(LoggableMessage<const char*>);
    static_assert(LoggableMessage<char*>);

    static_assert(!LoggableMessage<int>);
    static_assert(!LoggableMessage<double>);
    static_assert(!LoggableMessage<float>);
    static_assert(!LoggableMessage<bool>);
    static_assert(!LoggableMessage<void*>);
}

TEST(LogConceptsTest, LogCategoryVerbocityShouldBeValid)
{
    static_assert(ValidVerbocityLevel<LogVerbosity::Display>);
    static_assert(ValidVerbocityLevel<LogVerbosity::Error>);
    static_assert(ValidVerbocityLevel<LogVerbosity::NoLogging>);
    static_assert(ValidVerbocityLevel<LogVerbosity::Fatal>);
    static_assert(ValidVerbocityLevel<LogVerbosity::Log>);
    static_assert(ValidVerbocityLevel<LogVerbosity::Warning>);
}