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
            layoutData.transform.getPosition(),
            layoutData.size * layoutData.transform.getScale(),
            colour,
            texture.toSharedPtr()
        );
    }

    void CDrawElementList::add(const SLayoutData& layoutData, SColour colour)
    {
        m_elements.emplace_back(
            layoutData.transform.getPosition(),
            layoutData.size * layoutData.transform.getScale(),
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
