#ifndef TAILS_WINDOW_IMPL_HPP
#define TAILS_WINDOW_IMPL_HPP

struct SDL_Window;

namespace tails::window::impl
{
    SDL_Window* getWindow();
}

#endif // TAILS_WINDOW_IMPL_HPP
