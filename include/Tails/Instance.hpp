#ifndef TAILS_INSTANCE_HPP
#define TAILS_INSTANCE_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/AssetManager.hpp>

#include <memory>

namespace tails
{
    class CEngine;
    
    class TAILS_API CInstance final
    {
    public:
        CInstance() = default;

        void init();
        void tick(float deltaTime);
        void draw();
        
        void main();

        std::unique_ptr<CEngine> engine;
        CAssetManager assetManager;
    };

    /**
     * Global program instance. Represents the running program as a whole, including any created windows,
     * the engine, its own general asset manager, etc.
     */
    extern CInstance gInstance;
}

#endif // TAILS_INSTANCE_HPP
