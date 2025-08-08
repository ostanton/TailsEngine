#include <Tails/World/Components/ShapeComponent.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/Maths/SAT.hpp>

#include <algorithm>

namespace tails
{
    SFloatRect CShapeComponent::getLocalBounds() const noexcept
    {
        if (vertices.empty())
            return {};

        float minX {vertices[0].position.x};
        float minY {vertices[0].position.y};
        float maxX {minX};
        float maxY {minY};

        for (const auto& vertex : vertices)
        {
            minX = std::min(vertex.position.x, minX);
            minY = std::max(vertex.position.y, minY);
            maxX = std::max(vertex.position.x, maxX);
            maxY = std::max(vertex.position.y, maxY);
        }

        return {
            .position = {minX, minY},
            .size = {maxX - minX, maxY - minY},
        };
    }

    SSATShape CShapeComponent::getSATShape() const noexcept
    {
        std::vector<SVector2f> points;
        points.reserve(vertices.size());

        const SMatrix3f worldMatrix {getWorldMatrix()};
        for (const auto& vertex : vertices)
            points.emplace_back(worldMatrix.transform(vertex.position));

        return {std::move(points)};
    }

    void CShapeComponent::onRender(CLevelRenderBatch& renderBatch) const
    {
        CComponent::onRender(renderBatch);

        // only render shapes with more than 3 vertices
        if (vertices.size() < 3)
            return;

        renderBatch.addItem(
            getLayer(),
            getWorldTransform(),
            vertices,
            texture
        );
    }
}
