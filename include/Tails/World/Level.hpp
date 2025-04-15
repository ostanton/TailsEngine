#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Core.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Assets/Asset.hpp>

#include <vector>
#include <memory>
#include <map>

namespace tails
{
    class CActor;
    class CString;
    class CLayer;
    class CCameraComponent;
    class CLevelLoader;

    /**
     * A game level, containing actors, layers, etc. to tick and render
     */
    class TAILS_API CLevel final : public IRenderItem, public IAsset
    {
        friend CLevelLoader;
        
    public:
        using ActorIterator = std::vector<std::unique_ptr<CActor>>::iterator;
        using ConstActorIterator = std::vector<std::unique_ptr<CActor>>::const_iterator;
        using LayersMap = std::map<int, CLayer>;
        using ActorsVector = std::vector<std::unique_ptr<CActor>>;

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
        template<typename T> T* spawnActor(const STransform2D& transform, int layer = 0);

        /**
         * Spawns a registered actor in the level, at the specified transform, in the specified layer,
         * and casts it to the specified actor class
         * @tparam T Actor class
         * @param name Class name
         * @param transform Target transform
         * @param layer Target layer
         * @return Spawned actor
         */
        template<typename T> T* spawnActor(const CString& name, const STransform2D& transform, int layer = 0);

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
        
        void onTick(float deltaSeconds);
        void onRender(IRenderer& renderer) const override;

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

    template<typename T>
    T* CLevel::spawnActor(const STransform2D& transform, const int layer)
    {
        return static_cast<T*>(spawnActor(std::make_unique<T>(), transform, layer));
    }

    template<typename T>
    T* CLevel::spawnActor(const CString& name, const STransform2D& transform, const int layer)
    {
        return static_cast<T*>(spawnActor(name, transform, layer));
    }
}

#endif // TAILS_LEVEL_HPP
