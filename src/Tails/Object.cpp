#include <Tails/Object.hpp>
#include <Tails/Serialisable.hpp>

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
        auto& registry = priv::getSerialisableRegistry();
        auto regIt = registry.find(name.data());

        if (regIt == registry.end())
        {
            CDebug::error("Object ", name, " does not exist in the registry.");
            return nullptr;
        }

        auto result = dynamic_cast<CObject*>(regIt->second());
        result->outer = outer;

        return result;
    }

    TUniqueObject<CObject> newObjectUnique(std::string_view name, CObject* outer)
    {
        return {newObject(name, outer), deleteObject};
    }

    void deleteObject(CObject* obj)
    {
        delete obj;
    }
}
