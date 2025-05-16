project(Tails)

target_sources(
    Tails
    PRIVATE
        WidgetSubsystem.cpp
        Widget.cpp
        Panel.cpp
        TransformedWidgets.cpp
        LayoutData.cpp
        LeafWidget.cpp
        Image.cpp
        CompoundWidget.cpp
)

add_subdirectory(Input)
add_subdirectory(Layout)
