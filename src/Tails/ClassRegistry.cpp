#include <Tails/ClassRegistry.hpp>
#include <Tails/Serialisable.hpp>

namespace tails
{
    CClassRegistry::CClassRegistry(const CClassRegistry& other)
    {
        
    }

    CClassRegistry::~CClassRegistry() = default;

    CClassRegistry& CClassRegistry::operator=(const CClassRegistry& other)
    {
        return *this;
    }

    void CClassRegistry::registerClass(const std::string& name, std::unique_ptr<ISerialisable> classObj)
    {
        classObj->m_className = name;
        m_classes.try_emplace(name, std::move(classObj));
    }

    std::unique_ptr<ISerialisable> CClassRegistry::instantiateClass(const std::string& name)
    {
        if (m_classes.contains(name))
        {
            // you are not expected to set className, etc. in the overriden class method.
            auto result = m_classes[name]->clone();
            if (result->m_className != name)
                result->m_className = name;
            return result;
        }

        return nullptr;
    }

    bool CClassRegistry::classExists(const std::string& name) const
    {
        return m_classes.contains(name);
    }
}
