project(Tails)

target_sources(
    Tails
    PRIVATE
        WidgetSubsystem.cpp
        Widget.cpp
        Panel.cpp
)

add_subdirectory(Layout)
