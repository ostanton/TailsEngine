#include <Tails/UI/Image.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/UI/Rendering/DrawElementList.hpp>

namespace tails::ui
{
    SVector2f CImage::getDesiredSize() const noexcept
    {
        if (!texture)
            return customSize;

        return useCustomSize ? customSize : SVector2f {texture->getSize()};
    }

    void CImage::onPaint(
        const SLayoutData& myLayout,
        CDrawElementList& drawElements,
        const float deltaSeconds
    ) const
    {
        if (texture)
            drawElements.add(
                myLayout,
                texture,
                tint
            );
        else
            drawElements.add(
                myLayout,
                tint
            );
        /*
        if (texture)
            render::texture(texture, myLayout.transform, myLayout.size, tint);
        else
            render::rect(myLayout.transform, myLayout.size, tint);
        */
    }
}
