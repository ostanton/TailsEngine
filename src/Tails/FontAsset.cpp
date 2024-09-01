#include <Tails/FontAsset.hpp>

namespace tails
{
    bool CFontAsset::load(const std::string& path)
    {
        return openFromFile(path);
    }

    std::string CFontAsset::getType() const
    {
        return "font";
    }
}
