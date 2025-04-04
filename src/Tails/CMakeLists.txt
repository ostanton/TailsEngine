project(Tails)

target_sources(
    Tails
    PRIVATE
        Log.cpp
        Profiler.cpp
        String.cpp
        Application.cpp
        EntryPoint.cpp
        Window.cpp
        Debug.cpp
)

add_subdirectory(Assets)
add_subdirectory(Game)
add_subdirectory(Input)
add_subdirectory(Maths)
add_subdirectory(Renderer)
add_subdirectory(SilverUI)
