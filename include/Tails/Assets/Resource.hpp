#ifndef TAILS_ASSETRESOURCE_HPP
#define TAILS_ASSETRESOURCE_HPP

#include <Tails/Config.hpp>

#include <string>

namespace tails
{
    class TAILS_API Resource
    {
        friend struct AssetInfo;

    public:
        virtual ~Resource() = default;

    protected:
        virtual bool load(const std::string& path) = 0;
    };
}

#endif // TAILS_ASSETRESOURCE_HPP
