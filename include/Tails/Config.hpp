#ifndef TAILS_CONFIG_HPP
#define TAILS_CONFIG_HPP

#define TAILS_API

#ifndef NDEBUG
#define TAILS_DEBUG
#endif // NDEBUG

#include <source_location>
#include <cstdint>

namespace tails
{
    constexpr const char* getFileName(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.file_name();
    }

    constexpr const char* getFunctionName(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.function_name();
    }

    constexpr std::uint_least32_t getLine(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.line();
    }

    constexpr std::uint_least32_t getColumn(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.column();
    }
} // tails

#endif // TAILS_CONFIG_HPP
