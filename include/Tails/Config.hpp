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

#endif // TAILS_CONFIG_HPP
