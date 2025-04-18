project(Tails)

target_sources(
    Tails
    PRIVATE
        WidgetSubsystem.hpp
        Widget.hpp
        Slot.hpp
        Panel.hpp
        LayoutData.hpp
        TransformedWidgets.hpp
        LeafWidget.hpp
        Image.hpp
        Alignment.hpp
        Orientation.hpp
        Visibility.hpp
        Margin.hpp
        CompoundWidget.hpp
)

add_subdirectory(Children)
add_subdirectory(Layout)
