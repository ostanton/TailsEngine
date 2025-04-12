#ifndef TAILS_LAYER_HPP
#define TAILS_LAYER_HPP

#include <Tails/Core.hpp>

#include <vector>

namespace tails
{
    class CActor;
    class CLevel;
    class IRenderer;
    
    /**
     * A layer within a level. Higher layers render in front of lower layers.
     */
    class TAILS_API CLayer final
    {
        friend CLevel;

    public:
        void onTick(float deltaSeconds);
        void onRender(IRenderer& renderer) const;
        
    private:
        void addActor(CActor* actor);
        void removeActor(const CActor* actor);
        
        std::vector<CActor*> m_actors;
        // layer effects, transform maybe, etc.
    };
}

#endif // TAILS_LAYER_HPP
