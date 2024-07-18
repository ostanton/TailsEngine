project(TailsEngine)

target_sources(
    TailsEngine
    PRIVATE
    Button.hpp
    ButtonSlot.hpp
    CanvasPanel.hpp
    CanvasSlot.hpp
    PanelSlot.hpp
    PanelWidget.hpp
    RectangleWidget.hpp
    Slot.hpp
    StackBox.hpp
    StackBoxSlot.hpp
    Widget.hpp
    WidgetNavigation.hpp
)

add_subdirectory(Layout)
