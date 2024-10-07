#include <Tails/Object.hpp>
#include <Tails/ClassRegistry.hpp>

namespace tails
{
    void CObject::markForCreate()
    {
        m_flags |= PendingCreate;
    }

    void CObject::unmarkForCreate()
    {
        m_flags &= ~PendingCreate;
    }

    void CObject::markForDestroy()
    {
        m_flags |= PendingDestroy;
    }

    void CObject::unmarkForDestroy()
    {
        m_flags &= ~PendingDestroy;
    }

    void CObject::clearFlags()
    {
        m_flags = 0;
    }
}
