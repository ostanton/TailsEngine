#include <Tails/Screen.hpp>

namespace tails
{
    void CScreen::preTick()
    {
        ITickable::preTick();
    }

    void CScreen::tick(float deltaTime)
    {
        
    }

    void CScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        
    }

    void CScreen::postTick()
    {
        ITickable::postTick();
    }
}
