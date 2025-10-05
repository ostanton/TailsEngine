#ifndef TAILS_SHAPE_COMPONENT_HPP
#define TAILS_SHAPE_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>
#include <Tails/Renderer/Vertex.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CTexture;

    /**
     * A convex shape component with a dynamic number of vertices
     */
    class TAILS_API CShapeComponent : public CComponent
    {
    public:
        /** The vertices which make up this ShapeComponent's shape */
        std::vector<SVertex> vertices;

        /** An optional texture to render on the shape */
        std::shared_ptr<CTexture> texture;

        [[nodiscard]] SFloatRect getLocalBounds() const noexcept override;
        [[nodiscard]] SSATShape getSATShape() const noexcept override;

    protected:
        void onRender(CLevelRenderBatch& renderBatch, int actorLayer) const override;
    };
}

#endif // TAILS_SHAPE_COMPONENT_HPP
