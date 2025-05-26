#ifndef TAILS_FORMAT_HPP
#define TAILS_FORMAT_HPP

#include <format>

/**
 * Basic string formatter, used in @code TAILS_LOG@endcode macro
 * @param FMT C++ std::format string
 */
#define TAILS_FMT(FMT, ...) ::std::format(FMT, __VA_ARGS__)

#endif // TAILS_FORMAT_HPP
