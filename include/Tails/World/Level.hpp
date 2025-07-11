#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Maths/Colour.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/World/Camera.hpp>

#include <vector>
#include <memory>
#include <map>

namespace tails
{
    class CActor;
    class CString;
    class CLayer;
    class CCameraComponent;
    class CTexture;
    class CLevel;

    /**
     * Render-only information for every entity's components in a level
     *
     * TODO - should probably take into account layers too. Can probably just
     * sort the items array by some layer number
     */
    class CLevelRenderBatch
    {
        friend CLevel;

    public:
        void addItem(
            const STransform2D& worldTransform,
            const SColour colour,
            const SVector2f size,
            const std::shared_ptr<CTexture>& texture
        )
        {
            items.emplace_back(worldTransform, colour, size, texture);
        }

    private:
        struct SItem
        {
            STransform2D transform;
            SColour colour;
            SVector2f size;
            std::shared_ptr<CTexture> texture;
        };

        std::vector<SItem> items;
        // TODO - some conversion from world space to screen space
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
         * this should be the last function called on the level, before it's make current
         */
        void loadFinished();

        /**
         * Call when loading a level from file, after spawning the actors
         */
        void initActors() const;

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
        void destroyActor(const CActor* actor);

        [[nodiscard]] SVector2f worldToScreen(SVector2f worldPoint) const;
        [[nodiscard]] STransform2D worldToScreen(const STransform2D& worldTransform) const;

        [[nodiscard]] SVector2f screenToWorld(SVector2f screenPoint) const;
        [[nodiscard]] STransform2D screenToWorld(const STransform2D& screenTransform) const;
        
        void onTick(float deltaSeconds);
        void onRender() const;

        /**
         * Deletes and erases any actors that are pending destroy
         */
        void cleanupActors();
        
        [[nodiscard]] ActorIterator getActorIterator(const CActor* actor);
        [[nodiscard]] ConstActorIterator getActorIterator(const CActor* actor) const;
        [[nodiscard]] const ActorsVector& getActors() const;

        [[nodiscard]] const LayersMap& getLayers() const;

        [[nodiscard]] EAssetType getAssetType() const noexcept override;

        CCameraComponent* activeCamera {nullptr};
        SCamera camera;

    private:
        [[nodiscard]] bool containsActor(const CActor* actor) const;
        [[nodiscard]] CLayer* getLayerFromActor(const CActor* actor);

        LayersMap m_layers;
        ActorsVector m_actors;
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
