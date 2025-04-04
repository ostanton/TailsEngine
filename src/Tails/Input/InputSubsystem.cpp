#include <Tails/Input/InputSubsystem.hpp>

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>

#include <iostream>

namespace tails
{
    namespace
    {
        SDL_Gamepad* gGamepad {nullptr};
        std::vector<SAction> gActions;
    }

    bool SActionValue::isActive() const noexcept
    {
        return get<bool>();
    }

    bool SAction::SKeyDataPair::isActive() const noexcept
    {
        return std::abs(input::getKeyValueNormalised(key) * magnitude) >= deadZone;
    }

    SAction::SAction(CString inName, std::vector<SKeyDataPair> inKeys)
        : name(std::move(inName))
        , keys(std::move(inKeys))
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

    namespace input
    {
        void init()
        {
            if (!SDL_HasGamepad())
            {
                std::cerr << "No gamepads connected!\n";
                return;
            }
        
            int count {0};
            auto joysticks = SDL_GetGamepads(&count);
            if (!joysticks)
            {
                std::cerr << "Failed to find gamepads!\n";
                SDL_free(joysticks);
                return;
            }

            std::cout << "Found " << count << " gamepads!\n";
            if (count <= 0)
                return;
        
            gGamepad = SDL_OpenGamepad(joysticks[0]);
            if (!gGamepad)
            {
                std::cerr << "Failed to open gamepad!\n";
            }

            SDL_free(joysticks);
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

        bool isKeyPressed(const SKey key)
        {
            return getKeyValueRaw(key) != 0;
        }

        i16 getKeyValueRaw(const SKey key)
        {
            constexpr i16 maxValue {32767};
            switch (key.type)
            {
            case EKeyType::Keyboard:
                if (auto const keyState = SDL_GetKeyboardState(nullptr);
                    keyState && keyState[SDL_GetScancodeFromKey(key.code, nullptr)])
                {
                    return maxValue;
                }
                break;
                
            case EKeyType::GamepadButton:
                return SDL_GetGamepadButton(gGamepad, static_cast<SDL_GamepadButton>(key.code)) ? maxValue : 0;
                
            case EKeyType::GamepadAxis:
                return SDL_GetGamepadAxis(gGamepad, static_cast<SDL_GamepadAxis>(key.code));
                
            case EKeyType::MouseButton:
                {
                    const auto mouseFlags = SDL_GetMouseState(nullptr, nullptr);
                    const auto keyMask = SDL_BUTTON_MASK(key.code);
                    return (mouseFlags & keyMask) == keyMask ? maxValue : 0;
                }
                
            case EKeyType::MouseMove:
            case EKeyType::MouseWheel:
                break;
            }
            return 0;
        }

        float getKeyValueNormalised(const SKey key)
        {
            return static_cast<float>(getKeyValueRaw(key)) / 32767.f; // max SDL axis value
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
}
