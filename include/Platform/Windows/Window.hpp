#ifndef TAILS_WIN32_WINDOW_HPP
#define TAILS_WIN32_WINDOW_HPP

#include <Tails/Renderer.hpp>
#include <Windows.h>

namespace tails::win32
{
    class CWindow final : public CRenderer
    {
        void render() override
        {
            
        }
        
        HWND m_handle {nullptr};
    };
}

#endif // TAILS_WIN32_WINDOW_HPP
