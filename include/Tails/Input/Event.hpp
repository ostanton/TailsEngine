#ifndef TAILS_WINDOW_EVENT_HPP
#define TAILS_WINDOW_EVENT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Input/Mouse.hpp>
#include <Tails/Templated/Variant.hpp>

namespace tails
{
    /**
     * Generic window event
     */
    class TAILS_API CEvent final
    {
    public:
        template<typename T>
        CEvent(const T& ev)
            : m_event(ev)
        {}

        struct SClosed {};
        struct SResized {SVector2i size;};
        struct SMouseButtonDown
        {
            mouse::EButton button;
            SVector2f position;
        };
        struct SMouseButtonUp
        {
            mouse::EButton button;
            SVector2f position;
        };
        struct SMouseLeft {};
        
        template<typename T>
        [[nodiscard]] bool is() const
        {
            return m_event.holdsAlternative<T>();
        }

        template<typename T>
        [[nodiscard]] const T* getIf() const
        {
            return m_event.get<T>();
        }
        
    private:
        TVariant<
            SClosed,
            SResized,
            SMouseButtonDown,
            SMouseButtonUp,
            SMouseLeft
        > m_event;
    };
}

#endif // TAILS_WINDOW_EVENT_HPP
