#ifndef TAILS_BUS_HPP
#define TAILS_BUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    class CAudioManager;
    class CResourceManager;
    
    class TAILS_API IBus
    {
        friend CAudioManager;
        
    public:
        virtual ~IBus() = default;

        template<ResourceType T>
        void setResource(T* resource)
        {
            setResourceImpl(resource);
        }
        
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;

    protected:
        virtual void setResourceImpl(void* resource) = 0;
    };
}

#endif // TAILS_BUS_HPP
