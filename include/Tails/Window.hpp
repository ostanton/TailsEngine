#ifndef TAILS_WINDOW_HPP
#define TAILS_WINDOW_HPP

#ifdef TAILS_BACKEND_SFML3
    #include <Platform/SFML3/Window.hpp>
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        #include <Platform/Windows/Window.hpp>
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
    #include <Tails/Renderer.hpp>
#endif // TAILS_BACKEND_SFML3

namespace tails
{
#ifdef TAILS_BACKEND_SFML3
    using CWindow = sfml3::CWindow;
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        using CWindow = win32::CWindow;
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
    class CWindow final : public CRenderer {};
#endif // TAILS_BACKEND_SFML3
}

#endif // TAILS_WINDOW_HPP
