#ifndef TAILS_INPUTDEVICE_HPP
#define TAILS_INPUTDEVICE_HPP

#include <Tails/Config.hpp>

namespace tails
{
    class TAILS_API IInputDevice
    {
    public:
        virtual ~IInputDevice() = default;
        
        virtual bool isButtonPressed(int button) = 0;
        virtual float getScalarInputValue(int input) {return 0;}
    };
}

#endif // TAILS_INPUTDEVICE_HPP
