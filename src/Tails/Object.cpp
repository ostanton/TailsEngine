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

    bool CObject::pendingCreate() const
    {
        return (m_flags & PendingCreate) == PendingCreate;
    }

    bool CObject::pendingDestroy() const
    {
        return (m_flags & PendingDestroy) == PendingDestroy;
    }

    CObject* newObject(std::string_view name, CObject* outer)
    {
        return newObject<CObject>(name, outer);
    }
}
