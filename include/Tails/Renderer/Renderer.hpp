#ifndef TAILS_RENDERER_HPP
#define TAILS_RENDERER_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/Colour.hpp>

struct SDL_Renderer;
struct SDL_Window;

namespace tails
{
    class IRenderItem;
    class CString;

    /**
     * Abstract class for rendering items
     */
    class TAILS_API IRenderer
    {
    public:
        IRenderer() = default;
        IRenderer(const IRenderer&) = default;
        IRenderer(IRenderer&&) noexcept = default;
        IRenderer& operator=(const IRenderer&) = default;
        IRenderer& operator=(IRenderer&&) noexcept = default;
        virtual ~IRenderer();

        void setRenderResolution(SVector2i resolution, bool integerScale = false);
        [[nodiscard]] SVector2i getRenderResolution() const;
        [[nodiscard]] bool isIntegerScaled() const;

        [[nodiscard]] SVector2i getOutputSize() const;
        [[nodiscard]] SDL_Window* getRenderWindow() const;
        
        void render(const IRenderItem& item);
        // TODO - pass in extra transform or something so rect is not absolute
        void render(const SFloatRect& rect, SColour colour = SColour::white) const;

        // TODO - various other render functions
        void renderText(const CString& string);

        void clear(SColour colour = SColour::black) const;
        void present() const;

    protected:
        SDL_Renderer* m_renderer;
    };
}

#endif // TAILS_RENDERER_HPP
