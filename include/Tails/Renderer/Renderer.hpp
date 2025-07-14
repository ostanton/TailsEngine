#ifndef TAILS_RENDERER_HPP
#define TAILS_RENDERER_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/Colour.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Templated/SharedRef.hpp>

#include <memory>

namespace tails
{
    class CString;
    class CTexture;
    class CFont;
}

// TODO - BIG CHANGE! favour rendering batches of vertices instead of hard texture/rect/text/etc
namespace tails::render
{
    TAILS_API void init();
    TAILS_API void deinit();
    TAILS_API void clear(SColour colour = SColour::black);
    TAILS_API void present();
    TAILS_API SVector2f getResolution();

    /**
     * Renders a textured rectangle
     * @param texture Texture ref
     * @param screenTransform Screen-space transform
     * @param size Local size. Can be 0 or {} for the texture's size
     * @param tint Tint colour
     * @param textureRect Portion of texture to render. Can be 0 or {} for the whole texture
     */
    TAILS_API void texture(
        const TSharedRef<CTexture>& texture,
        const STransform2D& screenTransform,
        SVector2f size,
        SColour tint = SColour::white,
        SIntRect textureRect = {}
    );

    /**
     * Renders a coloured rectangle
     * @param screenTransform Screen-space transform
     * @param size Local size
     * @param fillColour Fill colour
     * @param outlineColour Outline colour
     */
    TAILS_API void rect(
        const STransform2D& screenTransform,
        SVector2f size,
        SColour fillColour = SColour::white,
        SColour outlineColour = SColour::transparent
    );

    /**
     * Renders debug text, only in debug builds
     * @param screenTransform Screen-space transform
     * @param string String to render
     * @param colour Colour of the text
     * @param font Target font
     */
    TAILS_API void debugText(
        const STransform2D& screenTransform,
        const CString& string,
        SColour colour = SColour::white,
        const std::shared_ptr<CFont>& font = nullptr
    );

    TAILS_API void quad(
        const STransform2D& screenTransform,
        SVector2f size,
        SColour colour = SColour::white
    );
}

#endif // TAILS_RENDERER_HPP
