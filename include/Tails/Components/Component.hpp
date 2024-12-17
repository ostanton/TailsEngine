#ifndef TAILS_COMPONENT_HPP
#define TAILS_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

namespace tails
{
    class CEntity;

    /**
     * Base class for entity components
     */
    class TAILS_API CComponent :
        public CObject,
        public ITickable
    {
        friend CEntity;
        
    public:
        [[nodiscard]] CEntity& getOwningEntity() const;

    protected:
        virtual void create() {}
        virtual void postCreate() {}
        virtual void destroy() {}
    };
}

#endif // TAILS_COMPONENT_HPP
