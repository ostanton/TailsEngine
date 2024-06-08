#ifndef TAILS_SUBSYSTEM_HPP
#define TAILS_SUBSYSTEM_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

namespace sf
{
    class RenderTarget;
}

namespace tails
{
    class Subsystem : public Object, public Tickable
    {
    protected:
        virtual void init() = 0;
        virtual void draw(sf::RenderTarget& target) {}
        virtual void deinit() {}
    };
}

#endif // TAILS_SUBSYSTEM_HPP
