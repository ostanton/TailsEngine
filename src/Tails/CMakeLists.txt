project(Tails)

target_sources(
    Tails
    PRIVATE
        Log.cpp
        Profiler.cpp
        String.cpp
        Application.cpp
        Debug.cpp
        Filesystem.cpp
        Animation.cpp
        Memory.cpp
        Assert.cpp
        Window.cpp
        WindowImpl.hpp
)

add_subdirectory(Assets)
add_subdirectory(Audio)
add_subdirectory(Input)
add_subdirectory(Maths)
add_subdirectory(Renderer)
add_subdirectory(UI)
add_subdirectory(World)
