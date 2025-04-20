#ifndef TAILS_RENDERER_HPP
#define TAILS_RENDERER_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/Colour.hpp>

#include <memory>

struct SDL_Renderer;
struct SDL_Surface;

namespace tails
{
    class IRenderItem;
    class CString;
    class CTexture;
    class CWindow;

    /**
     * Renderer which can be used with a window (GPU rendering via graphics context)
     * or without (software rendering)
     */
    class TAILS_API CRenderer final
    {
    public:
        /**
         * Create a software renderer without a window
         * @param size Rendering surface size
         */
        CRenderer(SVector2u size);
        
        /**
         * Create a renderer for the specified window
         * @param window Target window
         */
        CRenderer(CWindow& window);
        CRenderer(const CRenderer&) = default;
        CRenderer(CRenderer&&) noexcept = default;
        CRenderer& operator=(const CRenderer&) = default;
        CRenderer& operator=(CRenderer&&) noexcept = default;
        ~CRenderer();

        // TODO - create camera and move this stuff to it instead?
        void setRenderResolution(SVector2i resolution, bool integerScale = false);
        [[nodiscard]] SVector2i getRenderResolution() const;
        [[nodiscard]] bool isIntegerScaled() const;

        [[nodiscard]] SVector2u getOutputSize() const;

        void render(const IRenderItem& item);
        // TODO - various other render functions
        // TODO - pass in extra transform or something so rect is not absolute
        void render(const SFloatRect& rect, SColour colour = SColour::white) const;
        
        /**
         * Renders a texture as an image to the screen
         * @param texture Texture asset to render
         * @param position Where on screen to render
         * @param size Size to override the texture's size. Set to 0 to keep texture size
         * @param tint Colour tint for the texture
         */
        void render(
            const std::shared_ptr<CTexture>& texture,
            SVector2f position,
            SVector2f size = {},
            SColour tint = SColour::white
        ) const;
        
        void render(const CString& string) const;
        void renderDebugText(
            SVector2f position,
            const CString& string,
            SColour colour = SColour::green
        ) const;

        [[nodiscard]] std::shared_ptr<CTexture> getOutputTexture() const noexcept;

        void clear(SColour colour = SColour::black) const;
        void present() const;

    protected:
        SDL_Renderer* m_renderer;
        CWindow* m_window;
        /** Surface we render to when using software rendering without a window */
        SDL_Surface* m_surface;
    };
}

#endif // TAILS_RENDERER_HPP
