#ifndef TAILS_INSTANCE_HPP
#define TAILS_INSTANCE_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Memory/UniquePtr.hpp>

namespace tails
{
    class CEngine;
    class CRenderer;
    
    class TAILS_API CInstance final
    {
    public:
        CInstance() = default;

        template<typename T>
        T* createRenderer()
        {
            renderer = makeUnique<T>();
            return renderer.get();
        }

        template<typename T>
        T* createEngine()
        {
            if (!renderer)
                createRenderer<CRenderer>();
            
            engine = makeUnique<T>(*renderer);
            return engine.get();
        }

        void init();
        void tick(float deltaTime);
        void draw();
        
        void main();

        TUniquePtr<CEngine> engine;
        TUniquePtr<CRenderer> renderer;
        CAssetManager assetManager;
    };

    /**
     * Global program instance. Represents the running program as a whole, including any created windows,
     * the engine, its own general asset manager, etc.
     */
    extern CInstance gInstance;
}

#endif // TAILS_INSTANCE_HPP
