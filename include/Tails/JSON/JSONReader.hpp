#ifndef TAILS_JSONREADER_HPP
#define TAILS_JSONREADER_HPP

#include <Tails/Config.hpp>

#include <nlohmann/json_fwd.hpp>

namespace tails
{
    class TAILS_API JSONReader
    {
    public:
        virtual JSONReader* read(const nlohmann::json&) = 0;
    };
}

#endif // TAILS_JSONREADER_HPP
