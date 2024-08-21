#include <Tails/FontAsset.hpp>

namespace tails
{
    bool CFontAsset::load(const std::string& path)
    {
        return loadFromFile(path);
    }

    std::string CFontAsset::getType() const
    {
        return "font";
    }
}
