#ifndef TAILS_LAYERCAMERA_HPP
#define TAILS_LAYERCAMERA_HPP

#include <Tails/Config.hpp>

#include <SFML/Graphics/View.hpp>

namespace tails
{
    class TAILS_API LayerCamera
    {
    public:
        void setPosition(const sf::Vector2f& pos);
        void setPosition(float x, float y);
        // It would be called resolution, but views are kind of resolution independent it seems, so no go!
        void setSize(const sf::Vector2f& size);
        void setSize(float width, float height);
        void setView(const sf::FloatRect& rect);
        void setView(const sf::View& view);
        inline const sf::View& getView() {return m_view;}

    private:
        sf::View m_view;
    };

} // tails

#endif //TAILS_LAYERCAMERA_HPP
