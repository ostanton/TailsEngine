#include <Tails/Object.hpp>

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

    bool CObject::pendingCreate() const
    {
        return (m_flags & PendingCreate) == PendingCreate;
    }

    bool CObject::pendingDestroy() const
    {
        return (m_flags & PendingDestroy) == PendingDestroy;
    }
}
