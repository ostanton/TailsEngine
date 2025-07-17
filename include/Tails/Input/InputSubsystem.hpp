#ifndef TAILS_INPUT_SUBSYSTEM_HPP
#define TAILS_INPUT_SUBSYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/Input/Keys.hpp>
#include <Tails/String.hpp>
#include <Tails/Templated/Variant.hpp>
#include <Tails/Delegates/MulticastDelegate.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Input/ActionHandle.hpp>

#include <vector>
#include <unordered_map>

/**
 * The input namespace contains input managing and handling structs, classes, and functions.
 * The input subsystem keeps track of the current state of existing actions, and updates them accordingly
 */
namespace tails::input
{
    /**
     * Decides when an action should be triggered and call its bound delegates
     */
    enum class EActionTrigger : u8
    {
        None,
        
        /** Called once when the action is first pressed */
        Pressed,
        
        /** Called every tick while the action is held */
        Held,
        
        /** Called once when the action is first released */
        Released
    };

    /**
     * An action's value, which can be digital or scalar (bool or float)
     */
    struct TAILS_API SActionValue final
    {
        SActionValue() = default;
        SActionValue(const bool val) : m_value(val ? 1.f : 0.f) {}
        SActionValue(const float val) : m_value(val) {}

        [[nodiscard]] bool operator==(const SActionValue& other) const noexcept;
        [[nodiscard]] bool operator!=(const SActionValue& other) const noexcept {return !(*this == other);}

        template<typename T>
        [[nodiscard]] T get() const noexcept
        {
            static_assert(sizeof(T) == 0, "Unsupported value type");
            return static_cast<T>(0);
        }

        [[nodiscard]] bool isActive() const noexcept;

        [[nodiscard]] bool operator<(const float other) const noexcept {return m_value < other;}
        [[nodiscard]] bool operator>(const float other) const noexcept {return m_value > other;}

    private:
        // scalar value, with digital values resolving to true if > 0.f
        float m_value;
    };

    TAILS_DECLARE_MULTICAST_DELEGATE_VA_PARAMS(SOnActionBinding, SActionValue);

    /**
     * Maps a number of keys to delegates that can be bound to
     */
    struct TAILS_API SAction
    {
        /**
         * Combines a key with extra data for an action
         */
        struct SKeyDataPair
        {
            SKeyDataPair(const SKey inKey)
                : key(inKey), magnitude(1.f), deadZone(0.1f)
            {}
            SKeyDataPair(const SKey inKey, const float inMagnitude)
                : key(inKey), magnitude(inMagnitude), deadZone(1.f)
            {}
            SKeyDataPair(const SKey inKey, const float inMagnitude, const float inDeadZone)
                : key(inKey), magnitude(inMagnitude), deadZone(inDeadZone)
            {}

            [[nodiscard]] bool isActive() const noexcept;
            
            SKey key;
            float magnitude;
            float deadZone;
        };

        /**
         * Contains the action delegate and the trigger which executes it
         */
        struct SActionDelegatePair
        {
            SActionDelegatePair(const EActionTrigger inTrigger, SOnActionBinding::Delegate binding)
                : trigger(inTrigger), bindingDelegate(std::move(binding))
            {}
            
            EActionTrigger trigger;
            SOnActionBinding bindingDelegate;
        };

        SAction(CString inName, std::vector<SKeyDataPair> inKeys);

        CString name;
        std::vector<SKeyDataPair> keys;
        SActionValue currentValue;
        SActionValue lastValue;
        std::unordered_map<EActionTrigger, SOnActionBinding> delegates;

        [[nodiscard]] bool isActive() const noexcept {return currentValue.isActive();}
        void bind(EActionTrigger triggerType, SOnActionBinding::Delegate binding);
    };

    TAILS_API void init();
    TAILS_API void tick();
    TAILS_API void deinit();
    TAILS_API [[nodiscard]] bool isKeyPressed(SKey key);
    TAILS_API [[nodiscard]] i16 getKeyValueRaw(SKey key);
    TAILS_API [[nodiscard]] float getKeyValueNormalised(SKey key);
    TAILS_API SActionHandle addAction(SAction action);
    TAILS_API [[nodiscard]] SAction* getActionFromName(const CString& name);
    TAILS_API [[nodiscard]] SVector2f getMousePosition(bool relativeToWindow = true);

    template<>
    inline bool SActionValue::get() const noexcept
    {
        // true if scalar is non-zero
        return m_value != 0.f;
    }

    template<>
    inline float SActionValue::get() const noexcept
    {
        return m_value;
    }
}

#endif // TAILS_INPUT_SUBSYSTEM_HPP
