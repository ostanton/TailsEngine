#include <Tails/ClassRegistry.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    CClassRegistry::~CClassRegistry() = default;

    void CClassRegistry::registerClass(const std::string& className, std::unique_ptr<ISerialisable> classObj)
    {
        classObj->m_className = className;
        CDebug::print("Registered " + className + " with typeid of " + typeid(classObj.get()).raw_name());
        m_classes.try_emplace(className, std::move(classObj));
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
