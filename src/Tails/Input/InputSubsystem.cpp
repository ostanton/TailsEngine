#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Log.hpp>
#include <Tails/Maths/Maths.hpp>

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_joystick.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>

namespace tails::input
{
    namespace
    {
        SDL_Gamepad* gGamepad {nullptr};
        std::vector<SAction> gActions;
    }

    bool SActionValue::operator==(const SActionValue& other) const noexcept
    {
        return maths::nearlyEqual(m_value, other.m_value, 0.01f);
    }

    bool SActionValue::isActive() const noexcept
    {
        return get<bool>();
    }

    bool SAction::SKeyDataPair::isActive() const noexcept
    {
        return std::abs(getKeyValueNormalised(key) * magnitude) >= deadZone;
    }

    SAction::SAction(CString inName, std::vector<SKeyDataPair> inKeys)
        : name(std::move(inName))
        , keys(std::move(inKeys))
        , currentValue()
        , lastValue()
    {
    }

    void SAction::bind(const EActionTrigger triggerType, SOnActionBinding::Delegate binding)
    {
        if (const auto it = delegates.find(triggerType); it != delegates.end())
        {
            it->second.add(std::move(binding));
            return;
        }

        delegates.try_emplace(triggerType, std::move(binding));
    }

    SAction* SActionHandle::getAction() const noexcept
    {
        if (index < gActions.size())
            return &gActions[index];
        
        return nullptr;
    }

    void init()
    {
        if (!SDL_HasGamepad())
        {
            TAILS_LOG(InputSubsystem, Message, "No gamepads connected");
            TAILS_LOG(InputSubsystem, Message, "Initialised");
            return;
        }

        int count {0};
        auto joysticks = SDL_GetGamepads(&count);
        if (!joysticks)
        {
            TAILS_LOG(InputSubsystem, Warning, "Failed to find gamepads");
            SDL_free(joysticks);
            TAILS_LOG(InputSubsystem, Message, "Initialised");
            return;
        }

        TAILS_LOG_VA(InputSubsystem, Message, "Found %d gamepads", count);
        if (count <= 0)
        {
            SDL_free(joysticks);
            TAILS_LOG(InputSubsystem, Message, "Initialised");
            return;
        }

        gGamepad = SDL_OpenGamepad(joysticks[0]);
        if (!gGamepad)
        {
            TAILS_LOG(InputSubsystem, Error, "Failed to open first gamepad");
        }
        else
        {
            TAILS_LOG_VA(InputSubsystem, Message, "Using '%s' gamepad", SDL_GetGamepadName(gGamepad));
        }

        SDL_free(joysticks);

        TAILS_LOG(InputSubsystem, Message, "Initialised");
    }

    void tick()
    {
        for (auto& action : gActions)
        {
            if (action.currentValue != action.lastValue)
                action.lastValue = action.currentValue;

            for (const auto& key : action.keys)
            {
                const bool active {key.isActive()};
                // TODO - get the sum of all active keys of this action instead of the first or most recent

                if (key.key.isDigital())
                {
                    if (active)
                    {
                        action.currentValue = key.magnitude;
                        break;
                    }

                    action.currentValue = false;
                }

                if (key.key.isScalar())
                {
                    if (const auto val = getKeyValueNormalised(key.key); active)
                    {
                        action.currentValue = val * key.magnitude;
                        break;
                    }

                    action.currentValue = 0.f;
                }
            }

            for (auto& [trigger, binding] : action.delegates)
            {
                switch (trigger)
                {
                case EActionTrigger::Pressed:
                    if (action.isActive() && !action.lastValue.isActive())
                        binding.broadcast({});
                    break;
                case EActionTrigger::Held:
                    if (action.isActive())
                        binding.broadcast(SActionValue {action.currentValue});
                    break;
                case EActionTrigger::Released:
                    if (!action.isActive() && action.lastValue.isActive())
                        binding.broadcast({});
                    break;
                case EActionTrigger::None:
                    break;
                }
            }
        }
    }

    void deinit()
    {
        gGamepad = nullptr;
        gActions.clear();

        TAILS_LOG(InputSubsystem, Message, "Deinitialised");
    }

    bool isKeyPressed(const SKey key)
    {
        return getKeyValueRaw(key) != 0;
    }

    i16 getKeyValueRaw(const SKey key)
    {
        switch (key.type)
        {
        case EKeyType::Keyboard:
            if (auto const keyState = SDL_GetKeyboardState(nullptr);
                keyState && keyState[SDL_GetScancodeFromKey(key.code, nullptr)])
            {
                return SDL_JOYSTICK_AXIS_MAX;
            }
            break;
            
        case EKeyType::GamepadButton:
            return SDL_GetGamepadButton(gGamepad, static_cast<SDL_GamepadButton>(key.code)) ? SDL_JOYSTICK_AXIS_MAX : 0;
            
        case EKeyType::GamepadAxis:
            return SDL_GetGamepadAxis(gGamepad, static_cast<SDL_GamepadAxis>(key.code));
            
        case EKeyType::MouseButton:
            {
                const auto mouseFlags = SDL_GetMouseState(nullptr, nullptr);
                const auto keyMask = SDL_BUTTON_MASK(key.code);
                return (mouseFlags & keyMask) == keyMask ? SDL_JOYSTICK_AXIS_MAX : 0;
            }
            
        case EKeyType::MouseMove:
        case EKeyType::MouseWheel:
            break;
        }
        return 0;
    }

    float getKeyValueNormalised(const SKey key)
    {
        return static_cast<float>(getKeyValueRaw(key)) / static_cast<float>(SDL_JOYSTICK_AXIS_MAX);
    }

    SActionHandle addAction(SAction action)
    {
        gActions.emplace_back(std::move(action));
        return {gActions.size() - 1};
    }

    SAction* getActionFromName(const CString& name)
    {
        for (auto& action : gActions)
        {
            if (action.name == name)
                return &action;
        }

        return nullptr;
    }
}
