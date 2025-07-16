#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Maths/Colour.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/OrientedRect.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/World/CollisionManager.hpp>

#include <vector>
#include <memory>
#include <map>

namespace tails
{
    class CActor;
    class CComponent;
    class CString;
    class CLayer;
    class CCameraComponent;
    class CTexture;
    class CLevel;
    struct SCamera;
    struct SSATShape;
    struct SVertex;

    /**
     * Render-only information for every entity's components in a level
     *
     * TODO - should probably take into account layers too. Can probably just
     * sort the items array by some layer number
     */
    class TAILS_API CLevelRenderBatch
    {
        friend CLevel;

    public:
        /**
         * Adds a filled rect item
         * @param worldTransform World-space transform
         * @param colour Fill colour
         * @param size Local size
         * @param texture Target texture
         */
        void addItem(
            const STransform2D& worldTransform,
            SColour colour,
            SVector2f size,
            std::shared_ptr<CTexture> texture
        );

        /**
         * Adds a filled convex shape via the target vertices. The vertices are transformed via the worldTransform
         * inside the function, and so must be in local-space to whatever is rendering them
         * @param worldTransform World-space transform
         * @param vertices Local vertices
         * @param texture Target texture
         */
        void addItem(
            const STransform2D& worldTransform,
            std::vector<SVertex> vertices,
            std::shared_ptr<CTexture> texture
        );

        /**
         * Adds a filled shape via the target vertices and indices. The vertices are transformed via the
         * worldTransform inside the function, and so must be in local-space to whatever is rendering them
         * @param worldTransform World-space transform
         * @param vertices Local vertices ordered anti-clockwise
         * @param indices Indices describing how the vertices connect
         * @param texture Target texture
         */
        void addItem(
            const STransform2D& worldTransform,
            std::vector<SVertex> vertices,
            std::vector<int> indices,
            std::shared_ptr<CTexture> texture
        );

    private:
        /**
         * A shape in world-space. Its vertices are transformed into world space from local space
         * when created, so does not need to store the world transform
         */
        struct SItem
        {
            std::vector<SVertex> vertices;
            std::vector<int> indices;
            std::shared_ptr<CTexture> texture;
        };

        std::vector<SItem> m_items;
    };

    /**
     * A game level, containing actors, layers, etc. to tick and render
     */
    class TAILS_API CLevel final : public IAsset
    {
    public:
        using ActorsVector = std::vector<std::unique_ptr<CActor>>;
        using ActorIterator = ActorsVector::iterator;
        using ConstActorIterator = ActorsVector::const_iterator;
        using LayersMap = std::map<int, CLayer>;

        CLevel();
        explicit CLevel(ActorsVector&& actors);
        explicit CLevel(ActorsVector&& actors, LayersMap&& layers);
        CLevel(const CLevel&) = delete;
        CLevel(CLevel&&) = delete;
        CLevel& operator=(const CLevel&) = delete;
        CLevel& operator=(CLevel&&) = delete;
        ~CLevel() override;

        /**
         * Call when the map finishes loading, and all actors, etc. are spawned. When loading from a file,
         * this should be the last function called on the level, before it's made current
         */
        void finishLoad();

        /**
         * Spawns an actor in the level, at the specified transform, in the specified layer
         * @tparam T Actor class
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        template<DerivedFrom<CActor> T> T* spawnActor(const STransform2D& transform, int layer = 0);

        /**
         * Spawns a registered actor in the level, at the specified transform, in the specified layer,
         * and casts it to the specified actor class
         * @tparam T Actor class
         * @param name Class name
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        template<DerivedFrom<CActor> T> T* spawnActor(const CString& name, const STransform2D& transform, int layer = 0);

        /**
         * Spawns an existing external actor in the level (as if it were spawned new),
         * at the specified transform, in the specified layer
         * @param actor Existing actor
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        CActor* spawnActor(std::unique_ptr<CActor> actor, const STransform2D& transform, int layer = 0);

        /**
         * Spawns a registered actor in the level, at the specified transform, in the specified layer
         * @param name Actor class name
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        CActor* spawnActor(const CString& name, const STransform2D& transform, int layer = 0);

        /**
         * Spawns an actor in the level, but does not call its setup functions. Treat it as incomplete.
         * Call @code finishActorSpawn@endcode to complete its construction
         * @param name Actor class name
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        CActor* spawnActorDeferred(const CString& name, const STransform2D& transform, int layer = 0);

        /**
         * Spawns an existing external actor in the level, but does not call its setup functions.
         * Treat it as incomplete. Call @code finishActorSpawn@endcode to complete its construction
         * @param actor Existing actor
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        CActor* spawnActorDeferred(std::unique_ptr<CActor> actor, const STransform2D& transform, int layer = 0);

        /**
         * Finalises construction of a deferred-spawned actor, spawning it fully
         * @param actor Actor to finalise
         */
        void finishActorSpawn(CActor* actor) const;

        void setActorLayer(CActor* actor, int layer);

        /**
         * Transforms a world-space point into screen-space via the active camera
         * @param worldPoint World-space point
         * @return Screen-space point
         */
        [[nodiscard]] SVector2f worldToScreen(SVector2f worldPoint) const noexcept;

        /**
         * Transforms a world-space AABB into screen-space via the active camera
         * @param worldRect World-space AABB
         * @return Screen-space AABB
         */
        [[nodiscard]] SFloatRect worldToScreen(const SFloatRect& worldRect) const noexcept;

        /**
         * Transform a world-space OBB into screen-space via the active camera
         * @param worldRect World-space OBB
         * @return Screen-space OBB
         */
        [[nodiscard]] SFloatOrientedRect worldToScreen(const SFloatOrientedRect& worldRect) const noexcept;

        /**
         * Transforms a world-space transform into screen-space via the active camera
         * @param worldTransform World-space transform
         * @return Screen-space transform
         */
        [[nodiscard]] STransform2D worldToScreen(const STransform2D& worldTransform) const noexcept;

        /**
         * Transforms a screen-space point into world-space via the active camera
         * @param screenPoint Screen-space point
         * @return World-space point
         */
        [[nodiscard]] SVector2f screenToWorld(SVector2f screenPoint) const noexcept;

        /**
         * Transforms a screen-space AABB into world-space via the active camera
         * @param screenRect Screen-space AABB
         * @return World-space AABB
         */
        [[nodiscard]] SFloatRect screenToWorld(const SFloatRect& screenRect) const noexcept;

        /**
         * Transforms a screen-space OBB into world-space via the active camera
         * @param screenRect Screen-space OBB
         * @return World-space OBB
         */
        [[nodiscard]] SFloatOrientedRect screenToWorld(const SFloatOrientedRect& screenRect) const noexcept;

        /**
         * Transforms a screen-space transform into world-space via the active camera
         * @param screenTransform Screen-space transform
         * @return World-space transform
         */
        [[nodiscard]] STransform2D screenToWorld(const STransform2D& screenTransform) const noexcept;

        void setActiveCamera(CCameraComponent* cameraComponent);

        /**
         * Referenced camera object should outlive how long it remains active for
         * @param camera New active camera reference
         */
        void setActiveCamera(SCamera& camera);

        [[nodiscard]] SCamera& getActiveCamera() noexcept;
        [[nodiscard]] const SCamera& getActiveCamera() const noexcept;
        [[nodiscard]] CCameraComponent* getActiveCameraComponent() noexcept;
        [[nodiscard]] const CCameraComponent* getActiveCameraComponent() const noexcept;

        void onTick(float deltaSeconds);
        void onRender() const;

        /**
         * Deletes and erases any actors that are pending destroy
         */
        void cleanupActors();

        /**
         * Gets the components which are currently colliding with the target component
         * @param component Component to check collisions on
         * @return Colliding components
         */
        [[nodiscard]] std::vector<CComponent*> getCollisionsFor(const CComponent* component) const noexcept;

        /**
         * Gets the actors whose components are currently colliding with the target actor's components
         * @param actor Actor to check collisions on
         * @return Colliding actors
         */
        [[nodiscard]] std::vector<CActor*> getCollisionsFor(const CActor* actor) const noexcept;

        [[nodiscard]] bool areColliding(const CComponent* compA, const CComponent* compB) const noexcept;
        [[nodiscard]] bool areColliding(const CActor* actorA, const CActor* actorB) const noexcept;

        [[nodiscard]] ActorIterator getActorIterator(const CActor* actor);
        [[nodiscard]] ConstActorIterator getActorIterator(const CActor* actor) const;
        [[nodiscard]] const ActorsVector& getActors() const;

        [[nodiscard]] const LayersMap& getLayers() const;

        [[nodiscard]] EAssetType getAssetType() const noexcept override;

    private:
        void initActors() const;
        [[nodiscard]] bool containsActor(const CActor* actor) const;
        [[nodiscard]] CLayer* getLayerFromActor(const CActor* actor);

        /*
         * TODO - rethink how we want to do layers (they can just be ints in the actors, no?)
         * Not sure how effects and other stuff would work, maybe a separate vector/map for each (SoA kinda thing).
         * Actors would just have their render batch sorted by their layer index then, instead of layers being
         * some weird view into the level actors vector
         */
        LayersMap m_layers;
        ActorsVector m_actors;

        CCollisionManager m_collisionManager;
        std::vector<std::pair<SSATShape, bool>> m_debugSATShapes;

        /**
         * Should never be null (is set on level load, etc.),
         * and generally points to a camera on a CCameraComponent (doesn't have to)
         *
         * TODO - could this be const?
         */
        SCamera* m_activeCamera {nullptr};
        /** The component which owns the active camera, can be null */
        CCameraComponent* m_activeCameraComponent {nullptr};
    };

    template<>
    [[nodiscard]] constexpr u8 getAssetType<CLevel>()
    {
        return static_cast<u8>(EAssetType::Level);
    }

    template<DerivedFrom<CActor> T>
    T* CLevel::spawnActor(const STransform2D& transform, const int layer)
    {
        return static_cast<T*>(spawnActor(std::make_unique<T>(), transform, layer));
    }

    template<DerivedFrom<CActor> T>
    T* CLevel::spawnActor(const CString& name, const STransform2D& transform, const int layer)
    {
        return static_cast<T*>(spawnActor(name, transform, layer));
    }
}

#endif // TAILS_LEVEL_HPP
