#ifndef TAILS_INT_HPP
#define TAILS_INT_HPP

#include <Tails/Config.hpp>

#include <cstdint>

namespace tails
{
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
}

#endif // TAILS_INT_HPP
