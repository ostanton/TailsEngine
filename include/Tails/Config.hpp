#ifndef TAILS_CONFIG_HPP
#define TAILS_CONFIG_HPP

#define TAILS_API

#ifndef NDEBUG
#define TAILS_DEBUG
#endif // NDEBUG

#ifdef TAILS_COMP_MSVC
#define TAILS_FUNCTION __FUNCSIG__
#elif TAILS_COMP_GNU
#define TAILS_FUNCTION __PRETTY_FUNCTION__
#else
// TODO - is this safe to just call __func__ like this?
#define TAILS_FUNCTION __func__
#endif // TAILS_COMP_MSVC

namespace tails
{
    /* Integer types */
    
    using int8 = signed char;
    using uint8 = unsigned char;

    using int16 = signed short;
    using uint16 = unsigned short;
    
    using int32 = signed int;
    using uint32 = unsigned int;

#ifdef TAILS_COMP_MSVC
    using int64 = signed __int64;
    using uint64 = unsigned __int64;
#else
    using int64 = signed long long;
    using uint64 = unsigned long long;
#endif // TAILS_COMP_MSVC
}

#endif // TAILS_CONFIG_HPP
