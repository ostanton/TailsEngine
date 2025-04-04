project(Tails)

target_sources(
    Tails
    PRIVATE
        Event.hpp
        EventPoller.hpp
        InputSubsystem.hpp
        Mouse.hpp
        Keys.hpp
        ActionHandle.hpp
)
