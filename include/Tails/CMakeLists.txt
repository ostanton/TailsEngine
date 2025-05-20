project(Tails)

target_sources(
    Tails
    PRIVATE
        Core.hpp
        Log.hpp
        Profiler.hpp
        String.hpp
        Application.hpp
        Debug.hpp
        Filesystem.hpp
        Window.hpp
        Animation.hpp
        Memory.hpp
        Concepts.hpp
        Assert.hpp
)

add_subdirectory(Assets)
add_subdirectory(Audio)
add_subdirectory(Delegates)
add_subdirectory(Input)
add_subdirectory(Maths)
add_subdirectory(Renderer)
add_subdirectory(Templated)
add_subdirectory(UI)
add_subdirectory(World)
