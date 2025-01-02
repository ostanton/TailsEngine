#include <Tails/Resources/Texture.hpp>

namespace tails
{
    sf::Vector2u CTexture::getSize() const
    {
        return m_texture.getSize();
    }

    bool CTexture::load(const std::filesystem::path& path)
    {
        return m_texture.loadFromFile(path);
    }

    const void* CTexture::getUnderlyingImpl() const
    {
        return &m_texture;
    }
}
