#ifndef TAILS_KEYS_HPP
#define TAILS_KEYS_HPP

#include <Tails/Core.hpp>

namespace tails
{
    enum class EKeyType : u8
    {
        Keyboard,
        MouseButton,
        MouseWheel,
        MouseMove,
        GamepadButton,
        GamepadAxis,
    };

    using KeyCode = u32;
    
    struct TAILS_API SKey final
    {
        KeyCode code;
        EKeyType type;

        [[nodiscard]] bool isScalar() const noexcept;
        [[nodiscard]] bool isDigital() const noexcept;

        [[nodiscard]] bool operator==(const SKey&) const noexcept = default;
        [[nodiscard]] bool operator!=(const SKey&) const noexcept = default;
    };

    /**
     * Static keys that function like an enum. At the moment it uses keycodes, but could
     * think about using scancodes in the future
     *
     * TODO - commented out keys I haven't got around to defining yet!
     */
    struct TAILS_API EKeys
    {
        // Keyboard & Mouse
        
        static const SKey A;
        static const SKey B;
        static const SKey C;
        static const SKey D;
        static const SKey E;
        static const SKey F;
        static const SKey G;
        static const SKey H;
        static const SKey I;
        static const SKey J;
        static const SKey K;
        static const SKey L;
        static const SKey M;
        static const SKey N;
        static const SKey O;
        static const SKey P;
        static const SKey Q;
        static const SKey R;
        static const SKey S;
        static const SKey T;
        static const SKey U;
        static const SKey V;
        static const SKey W;
        static const SKey X;
        static const SKey Y;
        static const SKey Z;

        static const SKey Zero;
        static const SKey One;
        static const SKey Two;
        static const SKey Three;
        static const SKey Four;
        static const SKey Five;
        static const SKey Six;
        static const SKey Seven;
        static const SKey Eight;
        static const SKey Nine;

        static const SKey Up;
        static const SKey Down;
        static const SKey Left;
        static const SKey Right;

        static const SKey Backspace;
        static const SKey Tab;
        static const SKey Enter;
        static const SKey SpaceBar;
        static const SKey CapsLock;
        static const SKey Escape;

        static const SKey Insert;
        static const SKey Home;
        static const SKey PageUp;
        static const SKey PageDown;
        static const SKey End;
        static const SKey Pause;

        static const SKey NumLock;
        static const SKey ScrollLock;

        static const SKey LeftMouseButton;
        static const SKey RightMouseButton;
        static const SKey MiddleMouseButton;
        static const SKey SpecialMouseButton1;
        static const SKey SpecialMouseButton2;

        static const SKey MouseX;
        static const SKey MouseY;
        static const SKey MouseScrollUp;
        static const SKey MouseScrollDown;

        static const SKey NumpadZero;
        static const SKey NumpadOne;
        static const SKey NumpadTwo;
        static const SKey NumpadThree;
        static const SKey NumpadFour;
        static const SKey NumpadFive;
        static const SKey NumpadSix;
        static const SKey NumpadSeven;
        static const SKey NumpadEight;
        static const SKey NumpadNine;

        //static const SKey Multiply;
        //static const SKey Add;
        //static const SKey Subtract;
        //static const SKey Divide;
        //static const SKey Decimal;

        //static const SKey F1;
        //static const SKey F2;
        //static const SKey F3;
        //static const SKey F4;
        //static const SKey F5;
        //static const SKey F6;
        //static const SKey F7;
        //static const SKey F8;
        //static const SKey F9;
        //static const SKey F10;
        //static const SKey F11;
        //static const SKey F12;

        //static const SKey LeftShift;
        //static const SKey RightShift;
        //static const SKey LeftCtrl;
        //static const SKey RightCtrl;
        //static const SKey LeftAlt;
        //static const SKey RightAlt;
        //static const SKey LeftCmd;
        //static const SKey RightCmd;

        //static const SKey Semicolon;
        //static const SKey Equals;
        //static const SKey Comma;
        //static const SKey Underscore;
        //static const SKey Hyphen;
        //static const SKey FullStop;
        //static const SKey ForwardSlash;
        //static const SKey Backslash;
        //static const SKey Tilde;
        //static const SKey LeftBracket;
        //static const SKey RightBracket;
        //static const SKey Apostrophe;
        //static const SKey Ampersand;
        //static const SKey Asterisk;
        //static const SKey Caret;
        //static const SKey Colon;
        //static const SKey Dollar;
        //static const SKey Exclamation;
        //static const SKey LeftSquareBracket;
        //static const SKey RightSquareBracket;

        // Gamepad

        static const SKey GamepadDPadUp;
        static const SKey GamepadDPadDown;
        static const SKey GamepadDPadLeft;
        static const SKey GamepadDPadRight;
        static const SKey GamepadFaceTop; // Triangle/Y
        static const SKey GamepadFaceBottom; // Cross/A
        static const SKey GamepadFaceLeft; // Square/X
        static const SKey GamepadFaceRight; // Circle/B
        static const SKey GamepadLeftShoulder;
        static const SKey GamepadRightShoulder;
        static const SKey GamepadSpecialLeft; // Select/Back
        static const SKey GamepadSpecialRight; // Start

        static const SKey GamepadLeftStickX;
        static const SKey GamepadLeftStickY;
        static const SKey GamepadRightStickX;
        static const SKey GamepadRightStickY;
        static const SKey GamepadLeftTriggerAxis;
        static const SKey GamepadRightTriggerAxis;
    };
}

#endif // TAILS_KEYS_HPP
