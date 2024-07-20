#ifndef TAILS_STATE_HPP
#define TAILS_STATE_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>

#include <vector>
#include <memory>
#include <string>

namespace tails
{
    class Layer;
    class Engine;

    /**
     * Base class for states (levels, UI screens, etc.)
     */
    class TAILS_API State : public Object, public sf::Drawable, public Tickable
    {
        friend Layer;

    public:
        State();
        ~State() override;

        [[nodiscard]] Layer& getLayer() const;

    protected:
        bool tickWhileInactive {false};
        bool drawWhileInactive {false};

        virtual void push() {} // called when pushed to the stack
        virtual void postPush() {} // called the start of the frame after being pushed
        virtual void pop() {} // called when popped from the stack
    };
}

#endif // TAILS_STATE_HPP
