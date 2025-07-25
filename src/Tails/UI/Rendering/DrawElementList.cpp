#include <Tails/UI/Rendering/DrawElementList.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/Renderer/Vertex.hpp>
#include <Tails/Renderer/Shapes.hpp>

namespace tails::ui
{
    void CDrawElementList::add(
        const SLayoutData& layoutData,
        const TSharedRef<CTexture>& texture,
        const SColour tint
    )
    {
        add(
            layoutData,
            shapes::quad(layoutData.size, tint),
            shapes::quadIndices(),
            texture.toSharedPtr()
        );
    }

    void CDrawElementList::add(const SLayoutData& layoutData, const SColour colour)
    {
        add(
            layoutData,
            shapes::quad(layoutData.size, colour),
            shapes::quadIndices(),
            nullptr
        );
    }

    void CDrawElementList::add(
        const SLayoutData& layoutData,
        std::vector<SVertex> vertices,
        std::shared_ptr<CTexture> texture
    )
    {
        std::vector<int> indices;
        indices.reserve(vertices.size() * 3);

        for (usize i {0}; i < vertices.size() - 1; i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(static_cast<int>(i));
            indices.emplace_back(static_cast<int>(i + 1));
        }

        add(layoutData, std::move(vertices), std::move(indices), std::move(texture));
    }

    void CDrawElementList::add(
        const SLayoutData& layoutData,
        std::vector<SVertex> vertices,
        std::vector<int> indices,
        std::shared_ptr<CTexture> texture
    )
    {
        for (auto& vertex : vertices)
            vertex.position = layoutData.transform.transformPoint(vertex.position);

        m_elements.emplace_back(std::move(vertices), std::move(indices), std::move(texture));
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
