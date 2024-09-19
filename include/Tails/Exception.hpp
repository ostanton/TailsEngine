#ifndef TAILS_EXCEPTION_HPP
#define TAILS_EXCEPTION_HPP

#include <Tails/Config.hpp>

#include <stdexcept>

namespace tails
{
    class TAILS_API CException final : public std::runtime_error
    {
    public:
        explicit CException(const std::string& message);
    };
}

#endif // TAILS_EXCEPTION_HPP
