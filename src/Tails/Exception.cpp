#include <Tails/Exception.hpp>

namespace tails
{
    CException::CException(const std::string& message) : std::runtime_error(message)
    {
    }
}
