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

    void CImage::onPaint(const SLayoutData& myLayout, const CRenderer& renderer, const float deltaSeconds) const
    {
        if (texture)
            renderer.render(texture, myLayout.transform.position, myLayout.size, tint);
        else
            renderer.render(myLayout.getRect(), tint);
    }
}
