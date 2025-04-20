#ifndef TAILS_LAYER_HPP
#define TAILS_LAYER_HPP

#include <Tails/Core.hpp>

#include <vector>

namespace tails
{
    class CActor;
    class CLevel;
    class CRenderer;
    
    /**
     * A layer within a level. Higher layers render in front of lower layers
     *
     * TODO - could make this completely hidden from user, in Level.cpp.
     * Might be worth having it exposed though if there's lots of options for a given layer. Just get the layer
     * from its number and call the function on it, instead of going through the level (level->setLayerShader()), etc.
     */
    class TAILS_API CLayer final
    {
        friend CLevel;

    public:
        void onTick(float deltaSeconds);
        void onRender(CRenderer& renderer) const;
        
    private:
        void addActor(CActor* actor);
        void removeActor(const CActor* actor);
        
        std::vector<CActor*> m_actors;
        // layer effects, transform maybe, etc.
    };
}

#endif // TAILS_LAYER_HPP
