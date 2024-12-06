#ifndef TAILS_IMAGE_WIDGET_HPP
#define TAILS_IMAGE_WIDGET_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/Widget.hpp>

#include <SFML/Graphics/VertexArray.hpp>

namespace sf
{
    class Texture;
}

namespace tails::ui
{
    /**
     * Essentially the widget version of a sprite
     */
    class TAILS_API CImage : public CWidget
    {
    public:
        void setTexture(const sf::Texture* texture);
        [[nodiscard]] const sf::Texture* getTexture() const;

        void setSize(sf::Vector2f size);
        [[nodiscard]] sf::Vector2f getSize() const;

        void setColour(sf::Color colour);
        [[nodiscard]] sf::Color getColour() const;

        [[nodiscard]] sf::FloatRect getLocalBounds() const override;
        
    protected:
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void updateTexCoords();

    private:
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip, 4};
        const sf::Texture* m_texture {nullptr};
    };
}

#endif // TAILS_IMAGE_WIDGET_HPP
