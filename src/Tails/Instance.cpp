#include <Tails/Instance.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    CInstance gInstance;

    void CInstance::main()
    {
        init();

        //while (engine->)
    }

    void CInstance::init()
    {
        if (!engine)
            engine = std::make_unique<CEngine>();
    }

    void CInstance::tick(float deltaTime)
    {
        
    }

    void CInstance::draw()
    {
        
    }
}
