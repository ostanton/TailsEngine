#include <Tails/ClassRegistry.hpp>

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
        return instantiateClass<ISerialisable>(name);
    }

    bool CClassRegistry::classExists(const std::string& name) const
    {
        return m_classes.contains(name);
    }
}
