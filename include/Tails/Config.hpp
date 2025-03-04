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
    TAILS_API constexpr const char* getFileName(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.file_name();
    }

    TAILS_API constexpr const char* getFunctionName(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.function_name();
    }

    TAILS_API constexpr auto getLine(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.line();
    }

    TAILS_API constexpr auto getColumn(const std::source_location& loc = std::source_location::current()) noexcept
    {
        return loc.column();
    }

    TAILS_API using u8 = std::uint8_t;
    TAILS_API using u16 = std::uint16_t;
    TAILS_API using u32 = std::uint32_t;
    TAILS_API using u64 = std::uint64_t;

    TAILS_API using i8 = std::int8_t;
    TAILS_API using i16 = std::int16_t;
    TAILS_API using i32 = std::int32_t;
    TAILS_API using i64 = std::int64_t;

    TAILS_API using f32 = float;
    TAILS_API using f64 = double;

    TAILS_API using usize = std::uintmax_t;
} // tails

#endif // TAILS_CONFIG_HPP
