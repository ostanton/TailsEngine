#ifndef TAILS_JSONREADER_HPP
#define TAILS_JSONREADER_HPP

namespace nlohmann
{
    class json;
}

namespace tails
{
    class JSONReader
    {
    public:
        virtual JSONReader* read(nlohmann::json&) = 0;
    };
}

#endif // TAILS_JSONREADER_HPP
