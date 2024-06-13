//
// Created by olive on 13/06/2024.
//

#include <Tails/Layers/LayerCamera.hpp>

namespace tails
{
    void LayerCamera::setPosition(const sf::Vector2f& pos)
    {
        m_view.setCenter(pos);
    }

    void LayerCamera::setPosition(float x, float y)
    {
        m_view.setCenter(x, y);
    }

    void LayerCamera::setSize(const sf::Vector2f& size)
    {
        m_view.setSize(size);
    }

    void LayerCamera::setSize(float width, float height)
    {
        m_view.setSize(width, height);
    }

    void LayerCamera::setView(const sf::FloatRect& rect)
    {
        m_view.setViewport(rect);
    }

    void LayerCamera::setView(const sf::View& view)
    {
        m_view = view;
    }
} // tails
