#ifndef TAILS_JSONREADER_HPP
#define TAILS_JSONREADER_HPP

#include <Tails/Config.hpp>

#include <nlohmann/json_fwd.hpp>

namespace tails
{
    class TAILS_API JSONReader
    {
    public:
        /**
         * Create a covariant return object of specified type from json object
         * @return Newly allocated object
         * @note Always check for a null return value!
         */
        virtual JSONReader* read(const nlohmann::json&) = 0;
    };
}

#endif // TAILS_JSONREADER_HPP
