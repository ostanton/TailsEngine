#include <Tails/Input/Keys.hpp>

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>

namespace tails::input
{
    const SKey EKeys::A {SDLK_A, EKeyType::Keyboard};
    const SKey EKeys::B {SDLK_B, EKeyType::Keyboard};
    const SKey EKeys::C {SDLK_C, EKeyType::Keyboard};
    const SKey EKeys::D {SDLK_D, EKeyType::Keyboard};
    const SKey EKeys::E {SDLK_E, EKeyType::Keyboard};
    const SKey EKeys::F {SDLK_F, EKeyType::Keyboard};
    const SKey EKeys::G {SDLK_G, EKeyType::Keyboard};
    const SKey EKeys::H {SDLK_H, EKeyType::Keyboard};
    const SKey EKeys::I {SDLK_I, EKeyType::Keyboard};
    const SKey EKeys::J {SDLK_J, EKeyType::Keyboard};
    const SKey EKeys::K {SDLK_K, EKeyType::Keyboard};
    const SKey EKeys::L {SDLK_L, EKeyType::Keyboard};
    const SKey EKeys::M {SDLK_M, EKeyType::Keyboard};
    const SKey EKeys::N {SDLK_N, EKeyType::Keyboard};
    const SKey EKeys::O {SDLK_O, EKeyType::Keyboard};
    const SKey EKeys::P {SDLK_P, EKeyType::Keyboard};
    const SKey EKeys::Q {SDLK_Q, EKeyType::Keyboard};
    const SKey EKeys::R {SDLK_R, EKeyType::Keyboard};
    const SKey EKeys::S {SDLK_S, EKeyType::Keyboard};
    const SKey EKeys::T {SDLK_T, EKeyType::Keyboard};
    const SKey EKeys::U {SDLK_U, EKeyType::Keyboard};
    const SKey EKeys::V {SDLK_V, EKeyType::Keyboard};
    const SKey EKeys::W {SDLK_W, EKeyType::Keyboard};
    const SKey EKeys::X {SDLK_X, EKeyType::Keyboard};
    const SKey EKeys::Y {SDLK_Y, EKeyType::Keyboard};
    const SKey EKeys::Z {SDLK_Z, EKeyType::Keyboard};

    const SKey EKeys::Zero {SDLK_0, EKeyType::Keyboard};
    const SKey EKeys::One {SDLK_1, EKeyType::Keyboard};
    const SKey EKeys::Two {SDLK_2, EKeyType::Keyboard};
    const SKey EKeys::Three {SDLK_3, EKeyType::Keyboard};
    const SKey EKeys::Four {SDLK_4, EKeyType::Keyboard};
    const SKey EKeys::Five {SDLK_5, EKeyType::Keyboard};
    const SKey EKeys::Six {SDLK_6, EKeyType::Keyboard};
    const SKey EKeys::Seven {SDLK_7, EKeyType::Keyboard};
    const SKey EKeys::Eight {SDLK_8, EKeyType::Keyboard};
    const SKey EKeys::Nine {SDLK_9, EKeyType::Keyboard};

    const SKey EKeys::Up {SDLK_UP, EKeyType::Keyboard};
    const SKey EKeys::Down {SDLK_DOWN, EKeyType::Keyboard};
    const SKey EKeys::Left {SDLK_LEFT, EKeyType::Keyboard};
    const SKey EKeys::Right {SDLK_RIGHT, EKeyType::Keyboard};

    const SKey EKeys::Backspace {SDLK_BACKSPACE, EKeyType::Keyboard};
    const SKey EKeys::Tab {SDLK_TAB, EKeyType::Keyboard};
    const SKey EKeys::Enter {SDLK_RETURN, EKeyType::Keyboard};
    const SKey EKeys::SpaceBar {SDLK_SPACE, EKeyType::Keyboard};
    const SKey EKeys::CapsLock {SDLK_CAPSLOCK, EKeyType::Keyboard};
    const SKey EKeys::Escape {SDLK_ESCAPE, EKeyType::Keyboard};

    const SKey EKeys::Insert {SDLK_INSERT, EKeyType::Keyboard};
    const SKey EKeys::Home {SDLK_HOME, EKeyType::Keyboard};
    const SKey EKeys::PageUp {SDLK_PAGEUP, EKeyType::Keyboard};
    const SKey EKeys::PageDown {SDLK_PAGEDOWN, EKeyType::Keyboard};
    const SKey EKeys::End {SDLK_END, EKeyType::Keyboard};
    const SKey EKeys::Pause {SDLK_PAUSE, EKeyType::Keyboard};

    const SKey EKeys::NumLock {SDL_KMOD_NUM, EKeyType::Keyboard};
    const SKey EKeys::ScrollLock {SDL_KMOD_SCROLL, EKeyType::Keyboard};

    const SKey EKeys::LeftMouseButton {SDL_BUTTON_LEFT, EKeyType::MouseButton};
    const SKey EKeys::RightMouseButton {SDL_BUTTON_RIGHT, EKeyType::MouseButton};
    const SKey EKeys::MiddleMouseButton {SDL_BUTTON_MIDDLE, EKeyType::MouseButton};
    const SKey EKeys::SpecialMouseButton1 {SDL_BUTTON_X1, EKeyType::MouseButton};
    const SKey EKeys::SpecialMouseButton2 {SDL_BUTTON_X2, EKeyType::MouseButton};

    const SKey EKeys::MouseX {static_cast<KeyCode>(EMouseAxis::X), EKeyType::MouseMove};
    const SKey EKeys::MouseY {static_cast<KeyCode>(EMouseAxis::Y), EKeyType::MouseMove};
    const SKey EKeys::MouseScrollUp {static_cast<KeyCode>(EMouseScrollDirection::Up), EKeyType::MouseWheel};
    const SKey EKeys::MouseScrollDown {static_cast<KeyCode>(EMouseScrollDirection::Down), EKeyType::MouseWheel};

    const SKey EKeys::NumpadZero {SDLK_KP_0, EKeyType::Keyboard};
    const SKey EKeys::NumpadOne {SDLK_KP_1, EKeyType::Keyboard};
    const SKey EKeys::NumpadTwo {SDLK_KP_2, EKeyType::Keyboard};
    const SKey EKeys::NumpadThree {SDLK_KP_3, EKeyType::Keyboard};
    const SKey EKeys::NumpadFour {SDLK_KP_4, EKeyType::Keyboard};
    const SKey EKeys::NumpadFive {SDLK_KP_5, EKeyType::Keyboard};
    const SKey EKeys::NumpadSix {SDLK_KP_6, EKeyType::Keyboard};
    const SKey EKeys::NumpadSeven {SDLK_KP_7, EKeyType::Keyboard};
    const SKey EKeys::NumpadEight {SDLK_KP_8, EKeyType::Keyboard};
    const SKey EKeys::NumpadNine {SDLK_KP_9, EKeyType::Keyboard};

    const SKey EKeys::GamepadDPadUp {SDL_GAMEPAD_BUTTON_DPAD_UP, EKeyType::GamepadButton};
    const SKey EKeys::GamepadDPadDown {SDL_GAMEPAD_BUTTON_DPAD_DOWN, EKeyType::GamepadButton};
    const SKey EKeys::GamepadDPadLeft {SDL_GAMEPAD_BUTTON_DPAD_LEFT, EKeyType::GamepadButton};
    const SKey EKeys::GamepadDPadRight {SDL_GAMEPAD_BUTTON_DPAD_RIGHT, EKeyType::GamepadButton};
    const SKey EKeys::GamepadFaceTop {SDL_GAMEPAD_BUTTON_NORTH, EKeyType::GamepadButton};
    const SKey EKeys::GamepadFaceBottom {SDL_GAMEPAD_BUTTON_SOUTH, EKeyType::GamepadButton};
    const SKey EKeys::GamepadFaceLeft {SDL_GAMEPAD_BUTTON_WEST, EKeyType::GamepadButton};
    const SKey EKeys::GamepadFaceRight {SDL_GAMEPAD_BUTTON_EAST, EKeyType::GamepadButton};
    const SKey EKeys::GamepadLeftShoulder {SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, EKeyType::GamepadButton};
    const SKey EKeys::GamepadRightShoulder {SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, EKeyType::GamepadButton};
    const SKey EKeys::GamepadSpecialLeft {SDL_GAMEPAD_BUTTON_BACK, EKeyType::GamepadButton};
    const SKey EKeys::GamepadSpecialRight {SDL_GAMEPAD_BUTTON_START, EKeyType::GamepadButton};

    const SKey EKeys::GamepadLeftStickX {SDL_GAMEPAD_AXIS_LEFTX, EKeyType::GamepadAxis};
    const SKey EKeys::GamepadLeftStickY {SDL_GAMEPAD_AXIS_LEFTY, EKeyType::GamepadAxis};
    const SKey EKeys::GamepadRightStickX {SDL_GAMEPAD_AXIS_RIGHTX, EKeyType::GamepadAxis};
    const SKey EKeys::GamepadRightStickY {SDL_GAMEPAD_AXIS_RIGHTY, EKeyType::GamepadAxis};
    const SKey EKeys::GamepadLeftTriggerAxis {SDL_GAMEPAD_AXIS_LEFT_TRIGGER, EKeyType::GamepadAxis};
    const SKey EKeys::GamepadRightTriggerAxis {SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, EKeyType::GamepadAxis};
}
