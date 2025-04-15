#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Core.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Maths/Transform2D.hpp>

#include <vector>
#include <memory>
#include <map>

namespace tails
{
    class CActor;
    class CString;
    class CLayer;
    
    class TAILS_API CLevel final : public IRenderItem
    {
    public:
        using ActorIterator = std::vector<std::unique_ptr<CActor>>::iterator;
        using ConstActorIterator = std::vector<std::unique_ptr<CActor>>::const_iterator;

        CLevel();
        CLevel(const CLevel&) = delete;
        CLevel(CLevel&&) = delete;
        CLevel& operator=(const CLevel&) = delete;
        CLevel& operator=(CLevel&&) = delete;
        ~CLevel() override;
        
        template<typename T>
        T* spawnActor(const STransform2D& transform, const int layer = 0)
        {
            return static_cast<T*>(spawnActor(std::make_unique<T>(), transform, layer));
        }

        template<typename T>
        T* spawnActor(const CString& name, const STransform2D& transform, const int layer = 0)
        {
            return static_cast<T*>(spawnActor(name, transform, layer));
        }

        void setActorLayer(CActor* actor, int layer);
        void destroyActor(const CActor* actor);
        
        void onTick(float deltaSeconds);
        void onRender(IRenderer& renderer) const override;
        
        CActor* spawnActor(std::unique_ptr<CActor> actor, const STransform2D& transform, int layer = 0);
        CActor* spawnActor(const CString& name, const STransform2D& transform, int layer = 0);

        /**
         * Deletes and erases any actors that are pending destroy
         */
        void cleanupActors();
        
        [[nodiscard]] ActorIterator getActorIterator(const CActor* actor);
        [[nodiscard]] ConstActorIterator getActorIterator(const CActor* actor) const;
        
    private:
        [[nodiscard]] bool containsActor(const CActor* actor) const;
        [[nodiscard]] CLayer* getLayerFromActor(const CActor* actor);

        std::map<int, CLayer> m_layers;
        std::vector<std::unique_ptr<CActor>> m_actors;
    };
}

#endif // TAILS_LEVEL_HPP
