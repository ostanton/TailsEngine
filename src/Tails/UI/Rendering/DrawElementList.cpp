#include <Tails/UI/Rendering/DrawElementList.hpp>
#include <Tails/UI/LayoutData.hpp>

namespace tails::ui
{
    void CDrawElementList::add(
        const SLayoutData& layoutData,
        const TSharedRef<CTexture>& texture,
        SColour colour
    )
    {
        m_elements.emplace_back(
            layoutData.transform.position,
            layoutData.size * layoutData.transform.scale2D,
            colour,
            texture.toSharedPtr()
        );
    }

    void CDrawElementList::add(const SLayoutData& layoutData, SColour colour)
    {
        m_elements.emplace_back(
            layoutData.transform.position,
            layoutData.size * layoutData.transform.scale2D,
            colour,
            nullptr
        );
    }

    CDrawElementList::Iterator CDrawElementList::begin()
    {
        return m_elements.begin();
    }

    CDrawElementList::Iterator CDrawElementList::end()
    {
        return m_elements.end();
    }

    CDrawElementList::ConstIterator CDrawElementList::begin() const
    {
        return m_elements.begin();
    }

    CDrawElementList::ConstIterator CDrawElementList::end() const
    {
        return m_elements.end();
    }
}
