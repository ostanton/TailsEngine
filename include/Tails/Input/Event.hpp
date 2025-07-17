#ifndef TAILS_WINDOW_EVENT_HPP
#define TAILS_WINDOW_EVENT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Templated/Variant.hpp>
#include <Tails/Input/Keys.hpp>

namespace tails
{
    /**
     * Generic input poller event
     */
    class TAILS_API CEvent final
    {
    public:
        CEvent() = default;
        CEvent(const CEvent&) = default;
        CEvent(CEvent&&) noexcept = default;
        CEvent& operator=(const CEvent&) = default;
        CEvent& operator=(CEvent&&) noexcept = default;

        template<typename T>
        CEvent(const T& ev)
            : m_event(ev)
        {}

        template<typename T>
        CEvent& operator=(const T& ev)
        {
            m_event = ev;
            return *this;
        }

        ~CEvent() = default;

        template<typename T, typename... ArgsT>
        void set(ArgsT&&... args)
        {
            m_event = T {std::forward<ArgsT>(args)...};
        }

        struct SClosed {};
        struct SResized
        {
            SVector2i size;
        };
        struct SMouseButtonDown
        {
            input::EMouseButton button;
            SVector2f position;
        };
        struct SMouseButtonUp
        {
            input::EMouseButton button;
            SVector2f position;
        };
        struct SMouseMove
        {
            SVector2f position;
        };
        struct SKeyDown
        {
            input::SKey key;
        };
        struct SKeyUp
        {
            input::SKey key;
        };

        template<typename T>
        [[nodiscard]] constexpr bool is() const
        {
            return m_event.holdsAlternative<T>();
        }

        template<typename T>
        [[nodiscard]] constexpr const T* getIf() const
        {
            return m_event.get<T>();
        }
        
    private:
        TVariant<
            SClosed,
            SResized,
            SMouseButtonDown,
            SMouseButtonUp,
            SMouseMove,
            SKeyDown,
            SKeyUp
        > m_event;
    };
}

#endif // TAILS_WINDOW_EVENT_HPP
