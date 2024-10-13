#ifndef TAILS_BUS_HPP
#define TAILS_BUS_HPP

#include <Tails/Config.hpp>

namespace tails
{
    class CAudioManager;
    
    class TAILS_API IBus
    {
        friend CAudioManager;
        
    public:
        virtual ~IBus() = default;
        
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void pause() = 0;
    };
}

#endif // TAILS_BUS_HPP
