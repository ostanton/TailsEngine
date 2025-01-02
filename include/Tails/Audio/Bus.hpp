#ifndef TAILS_BUS_HPP
#define TAILS_BUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    class CAudioManager;
    class CSoundBuffer;
    
    class TAILS_API IBus
    {
        friend CAudioManager;
        
    public:
        IBus() = default;
        IBus(const IBus&) = default;
        IBus(IBus&&) = default;
        IBus& operator=(const IBus&) = default;
        IBus& operator=(IBus&&) = default;
        virtual ~IBus() = default;

        template<Derives<CSoundBuffer> T>
        void setResource(const std::shared_ptr<T>& resource)
        {
            setResourceImpl(resource);
        }
        
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;

    protected:
        // TODO - make more generic base sound resource
        virtual void setResourceImpl(const std::shared_ptr<CSoundBuffer>& resource) = 0;
    };
}

#endif // TAILS_BUS_HPP
