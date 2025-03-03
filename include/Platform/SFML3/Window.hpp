#ifndef TAILS_SFML3_WINDOW_HPP
#define TAILS_SFML3_WINDOW_HPP

#include <Tails/Renderer.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace tails::sfml3
{
    class CWindow final : public CRenderer
    {
        void render() override
        {
            //m_window.draw();
        }
        
        sf::RenderWindow m_window;
    };
}

#endif // TAILS_SFML3_WINDOW_HPP
