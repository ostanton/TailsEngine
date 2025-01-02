#ifndef TAILS_FONT_RESOURCE_HPP
#define TAILS_FONT_RESOURCE_HPP

#include <Tails/Config.hpp>
#include <Tails/Resources/Resource.hpp>

#include <SFML/Graphics/Font.hpp>

namespace tails
{
    class TAILS_API CFont final : public IResource
    {
    private:
        bool load(const std::filesystem::path& path) override;
        const void* getUnderlyingImpl() const override;
        
        sf::Font m_font;
    };
}

#endif // TAILS_FONT_RESOURCE_HPP
