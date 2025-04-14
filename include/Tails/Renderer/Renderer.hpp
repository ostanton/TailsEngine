#ifndef TAILS_RENDERER_HPP
#define TAILS_RENDERER_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/Colour.hpp>

#include <memory>

struct SDL_Renderer;
struct SDL_Window;

namespace tails
{
    class IRenderItem;
    class CString;
    class CTexture;

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

        // TODO - create camera and move this stuff to it instead, or have camera inherit this
        void setRenderResolution(SVector2i resolution, bool integerScale = false);
        [[nodiscard]] SVector2i getRenderResolution() const;
        [[nodiscard]] bool isIntegerScaled() const;

        [[nodiscard]] SVector2i getOutputSize() const;
        [[nodiscard]] SDL_Window* getRenderWindow() const;
        
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

        void clear(SColour colour = SColour::black) const;
        void present() const;

    protected:
        SDL_Renderer* m_renderer;
    };
}

#endif // TAILS_RENDERER_HPP
