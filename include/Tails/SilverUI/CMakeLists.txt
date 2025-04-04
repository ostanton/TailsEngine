project(Tails)

target_sources(
    Tails
    PRIVATE
        WidgetSubsystem.hpp
        Widget.hpp
        Slot.hpp
        Panel.hpp
)

add_subdirectory(Layout)
