#ifndef TAILS_STATE_HPP
#define TAILS_STATE_HPP

#include <Tails/Object.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

namespace tails
{
    class StateStack;

    class State : public Object, public sf::Drawable
    {
        friend StateStack;

    public:
        virtual ~State() = default;

        StateStack& getStateStack();

        void setCameraPosition(const sf::Vector2f& position);
        void setCameraPosition(float x, float y);
        void setCameraResolution(const sf::Vector2f& resolution);
        void setCameraResolution(float w, float h);
        void setCamera(const sf::FloatRect& rectangle);
        void setCamera(const sf::View& camera);
        const sf::View& getCamera() {return m_camera;}

    protected:
        bool tickWhileInactive {false};
        bool drawWhileInactive {true};

        virtual void added() {} // called when added to the stack
        virtual void removed() {} // called when removed from the stack

        virtual void tick(float deltaTime) {}

        sf::View m_camera {sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)};
    };
}

#endif // TAILS_STATE_HPP
