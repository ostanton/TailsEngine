#ifndef TAILS_ASSETDATA_HPP
#define TAILS_ASSETDATA_HPP

#include <Tails/Config.hpp>

#include <string>

namespace tails
{
    class TAILS_API IAssetData
    {
    public:
        virtual ~IAssetData() = default;
        virtual bool load(const std::string& path) = 0;

        /**
         * Gets the asset type (texture, sound, etc.) as seen in the assets json
         * @return Type as string
         */
        virtual std::string getType() = 0;
    };
}

#endif // TAILS_ASSETDATA_HPP
