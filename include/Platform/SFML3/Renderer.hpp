#ifndef TAILS_SFML_RENDERER_HPP
#define TAILS_SFML_RENDERER_HPP

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails::sfml
{
    class CRenderer final
    {
        sf::RenderTarget m_target;
    };
}

#endif // TAILS_SFML_RENDERER_HPP
