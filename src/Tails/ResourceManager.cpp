#include <Tails/ResourceManager.hpp>

namespace tails
{
    CResourceManager& CResourceManager::get()
    {
        static CResourceManager instance;
        return instance;
    }
}
