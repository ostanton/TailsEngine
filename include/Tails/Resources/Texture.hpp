#ifndef TAILS_TEXTURE_RESOURCE_HPP
#define TAILS_TEXTURE_RESOURCE_HPP

#include <Tails/Config.hpp>
#include <Tails/Resources/Resource.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace tails
{
    class TAILS_API CTexture final : public IResource
    {
    public:
        [[nodiscard]] sf::Vector2u getSize() const;
        
    private:
        bool load(const std::filesystem::path& path) override;
        const void* getUnderlyingImpl() const override;

        sf::Texture m_texture;
    };
}

#endif // TAILS_TEXTURE_RESOURCE_HPP
