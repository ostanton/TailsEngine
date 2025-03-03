#ifndef TAILS_RENDERER_HPP
#define TAILS_RENDERER_HPP

#include <Tails/Config.hpp>

namespace tails
{
    /**
     * Base class for any kind of "surface" for which to render something onto
     */
    class TAILS_API CRenderer
    {
    public:
        CRenderer() = default;
        CRenderer(const CRenderer&) = default;
        CRenderer(CRenderer&&) noexcept = default;
        CRenderer& operator=(const CRenderer&) = default;
        CRenderer& operator=(CRenderer&&) noexcept = default;
        virtual ~CRenderer() = default;

        virtual void render() {}
    };
}

#endif // TAILS_RENDERER_HPP
