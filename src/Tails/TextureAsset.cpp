#include <Tails/TextureAsset.hpp>

namespace tails
{
    bool CTextureAsset::load(const std::string& path)
    {
        return loadFromFile(path);
    }
}
