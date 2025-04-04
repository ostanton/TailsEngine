#ifndef TAILS_EVENT_POLLER_HPP
#define TAILS_EVENT_POLLER_HPP

#include <Tails/Core.hpp>
#include <Tails/Input/Event.hpp>
#include <Tails/Templated/Optional.hpp>

namespace tails
{
    class TAILS_API IEventPoller
    {
    public:
        IEventPoller() = default;
        IEventPoller(const IEventPoller&) = default;
        IEventPoller(IEventPoller&&) noexcept = default;
        IEventPoller& operator=(const IEventPoller&) = default;
        IEventPoller& operator=(IEventPoller&&) noexcept = default;
        virtual ~IEventPoller() = default;

        virtual TOptional<CEvent> pollEvent() = 0;
    };
}

#endif // TAILS_EVENT_POLLER_HPP
