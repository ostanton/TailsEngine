#ifndef TAILS_LEVEL_HPP
#define TAILS_LEVEL_HPP

#include <Tails/Core.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Maths/Transform2D.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class CActor;
    
    class TAILS_API CLevel final : public IRenderItem
    {
    public:
        using ActorIterator = std::vector<std::unique_ptr<CActor>>::iterator;
        using ConstActorIterator = std::vector<std::unique_ptr<CActor>>::const_iterator;
        
        template<typename T>
        T* spawnActor(const STransform2D& transform)
        {
            return static_cast<T*>(spawnActor(std::make_unique<T>(), transform));
        }

        void destroyActor(const CActor* actor);
        
        void onTick(float deltaSeconds);
        void onRender(IRenderer& renderer) const override;
        
        CActor* spawnActor(std::unique_ptr<CActor> actor, const STransform2D& transform);
        void cleanupActors();
        
        [[nodiscard]] ActorIterator getActorIterator(const CActor* actor);
        [[nodiscard]] ConstActorIterator getActorIterator(const CActor* actor) const;
        
    private:
        [[nodiscard]] bool containsActor(const CActor* actor) const;
        
        std::vector<std::unique_ptr<CActor>> m_actors;
    };
}

#endif // TAILS_LEVEL_HPP
