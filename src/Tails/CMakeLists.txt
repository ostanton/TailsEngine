project(Tails)

target_sources(
    Tails
    PRIVATE
        Log.cpp
        Profiler.cpp
        String.cpp
        Application.cpp
        Window.cpp
        Debug.cpp
)

add_subdirectory(Assets)
add_subdirectory(Audio)
add_subdirectory(Input)
add_subdirectory(Maths)
add_subdirectory(Renderer)
add_subdirectory(SilverUI)
add_subdirectory(World)
