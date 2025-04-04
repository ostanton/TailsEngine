project(Tails)

target_sources(
    Tails
    PRIVATE
        Core.hpp
        Log.hpp
        Profiler.hpp
        String.hpp
        Application.hpp
        EntryPoint.hpp
        Window.hpp
        Debug.hpp
)

add_subdirectory(Assets)
add_subdirectory(Delegates)
add_subdirectory(Game)
add_subdirectory(Input)
add_subdirectory(Maths)
add_subdirectory(Renderer)
add_subdirectory(SilverUI)
add_subdirectory(Templated)
