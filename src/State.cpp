#include <Tails/State.hpp>
#include <Tails/StateStack.hpp>

namespace tails
{
    StateStack& State::getStateStack()
    {
        return *getTypedOuter<StateStack>();
    }

    void State::setCameraPosition(const sf::Vector2f& position)
    {
        m_camera.setCenter(position);
    }

    void State::setCameraPosition(float x, float y)
    {
        m_camera.setCenter(x, y);
    }

    void State::setCameraResolution(const sf::Vector2f& resolution)
    {
        m_camera.setSize(resolution);
    }

    void State::setCameraResolution(float w, float h)
    {
        m_camera.setSize(w, h);
    }

    void State::setCamera(const sf::FloatRect& rectangle)
    {
        m_camera.setViewport(rectangle);
    }

    void State::setCamera(const sf::View& camera)
    {
        m_camera = camera;
    }
}
