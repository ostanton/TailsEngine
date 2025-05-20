#include <Tails/UI/Image.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/UI/LayoutData.hpp>

namespace tails::ui
{
    SVector2f CImage::getDesiredSize() const noexcept
    {
        if (!texture)
            return customSize;

        return useCustomSize ? customSize : SVector2f {texture->getSize()};
    }

    void CImage::onPaint(const SLayoutData& myLayout, const float deltaSeconds) const
    {
        if (texture)
            render::texture(texture, myLayout.transform, myLayout.size, tint);
        else
            render::rect(myLayout.transform, myLayout.size, tint);
    }
}
