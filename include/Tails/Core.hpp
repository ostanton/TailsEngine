#ifndef TAILS_CORE_HPP
#define TAILS_CORE_HPP

#ifndef NDEBUG
    #define TAILS_DEBUG
#endif // NDEBUG

// See https://sourceforge.net/p/predef/wiki/Home/
#ifdef _WIN32
    #define TAILS_OS_WIN32
    #ifndef NOMINMAX
        #define NOMINMAX // no min & max macros
    #endif // NOMINMAX
#elif defined(__APPLE__) // _WIN32
    #define TAILS_OS_APPLE
#elif defined(__unix__) // defined(__APPLE__)
    #if defined(__linux__)
        #define TAILS_OS_LINUX
    #else // defined(__linux__)
        #error Tails: UNIX system is not supported
    #endif // defined(__linux__)
#elif defined(__PSP__) || defined(PSP) // defined(__unix__)
    #define TAILS_OS_PSP
#else // defined(__unix__)
    #define TAILS_OS_UNKNOWN
#endif // _WIN32

#ifdef _MSC_VER
    #define TAILS_COMPILER_MSVC
#elif defined(__GNUC__) // _MSC_VER
    #define TAILS_COMPILER_GCC
#elif defined(__clang__) // defined(__GNUC__)
    #define TAILS_COMPILER_CLANG
#else // defined(__clang__)
    #define TAILS_COMPILER_UNKNOWN
#endif // _MSC_VER

// TODO - import DLLs
#ifdef TAILS_OS_WIN32
    #ifdef TAILS_BUILD_SHARED
        #define TAILS_API __declspec(dllexport)
    #else // TAILS_BUILD_SHARED
        #define TAILS_API
    #endif // TAILS_BUILD_SHARED
#else // TAILS_OS_WIN32
    #define TAILS_API
#endif // TAILS_OS_WIN32

#ifdef TAILS_COMPILER_MSVC
    #define TAILS_FUNCTION_NAME __FUNCSIG__
#else // TAILS_COMPILER_MSVC
    #define TAILS_FUNCTION_NAME __FUNCTION__
#endif // TAILS_COMPILER_MSVC

#define TAILS_FILE_NAME __FILE__
#define TAILS_LINE __LINE__

#include <cstdint>
#include <cstddef>

/**
 * The tails namespace contains everything from the Tails Engine. It has namespaces within it for the
 * different subsystems
 */
namespace tails
{
    using u8 = std::uint8_t;
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;
    using u64 = std::uint64_t;

    using i8 = std::int8_t;
    using i16 = std::int16_t;
    using i32 = std::int32_t;
    using i64 = std::int64_t;

    using usize = std::size_t;
    using isize = std::intmax_t;
}

#endif // TAILS_CORE_HPP
