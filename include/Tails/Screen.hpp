#ifndef TAILS_SCREEN_HPP
#define TAILS_SCREEN_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    /**
     * Acts like a level for widgets.
     */
    class TAILS_API CScreen final : public CObject, public ITickable, public sf::Drawable
    {
    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
    };
}

#endif // TAILS_SCREEN_HPP
