#ifndef TAILS_KEYBOARDDEVICE_HPP
#define TAILS_KEYBOARDDEVICE_HPP

#include <Tails/Config.hpp>
#include <Tails/InputDevice.hpp>

namespace tails
{
    class TAILS_API CKeyboardDevice final : public IInputDevice
    {
    private:
        bool isButtonPressed(int button) override;
    };
}

#endif // TAILS_KEYBOARDDEVICE_HPP
