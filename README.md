# Tails Engine

[Devlogs on the development of this engine](https://www.youtube.com/playlist?list=PL8y2eQUFF8A-a4O3URQ2i6lYfzapD0ouc).

The *Tails Engine* is a simple, 2D library intended to somewhat mimic the style of Gameboy Advance games. It uses C++, with SFML as the windowing, drawing, etc. library, and nlohmann's json library to read and write JSON. CMake is also used as a build system, with [CPM](https://github.com/cpm-cmake/CPM.cmake) to download the "packages". It is not at all production ready (it's both an ever-changing codebase/API, and is not very stable), and isn't intended to be used for anything large, or even anything outside my own personal uses, but you are free to use it for whatever, provided it falls within the bounds of the licenses of SFML, etc.

> Documentation and examples will be held in separate places. Documentation will be on the wiki part of this repository (when I get around to writing it), and examples will be in a separate repository.

- [Features](#features)
- [How to compile](#how-to-compile)
  - [Dependencies](#dependencies)
    - [Software](#software)
    - [Libraries](#libraries)
  - [Compilers](#compilers)
- [Integration (make a game with it!)](#integration)

## Features

- Locked internal resolution that maintains its aspect ratio (black bars!),
- Clearly named classes and structures (classes prefixed with 'C', structures prefixed with 'S', interfaces prefixed with 'I', etc.),
- "Context-specific" resource manager (per-level/any object) that owns its resources via `unique_ptr`s, capable of holding any `ResourceType` concept-compliant object,
- Input manager with support for keyboard, mouse, and Xbox controllers (currently only tested with an Xbox 1 controller),
- Class registry, allowing support of allocating a new object of the correct type just from a string ID value (generally just its class name as a string),
- Unreal Engine-style entities (actors) and components (*not* an ECS).
- Unreal Engine-style slot-based UI framework (WIP)

## How to compile

Like with any other CMake project, you can clone the repository, create a build folder, and `cmake ..` in it. Then `make`, open the generated solution, etc. for whatever you generated for. Like so:
```
mkdir build
cd build
cmake ..
make
```

### Dependencies

#### Software

- C++20
- [CMake](https://cmake.org/)
- [CPM](https://github.com/cpm-cmake/CPM.cmake) -- automatically downloaded

#### Libraries

The dependent libraries are downloaded by CMake automatically via [CPM](https://github.com/cpm-cmake/CPM.cmake). This means you must have an internet connection for the first build generation. You do not require one for subsequent builds.

- [SFML 3](https://www.sfml-dev.org/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [LDtkLoader](https://github.com/Madour/LDtkLoader)

### Compilers

I mainly use MSVC and GCC to compile this project. MSVC because my main machine is running Windows, and GCC because the laptop I use to also work on this project is running Linux. Both compilers compile this project just fine.

I have tested with Clang, but it does not compile due to an issue with the standard library (I think). It would be nice if there was information online about it!

## Integration

It *should* work just fine if you download the repo via `FetchContent` or CPM, and just link against `TailsEngine`.

For example:

```cmake
cmake_minimum_required(VERSION 3.28.3)
project(TestGameProj)

# CPM (download/install CPM first!)
CPMAddPackage("gh:ostanton/TailsEngine#master")

# FetchContent
include(FetchContent)
FetchContent_Declare(
    TailsEngine
    GIT_REPOSITORY https://github.com/ostanton/TailsEngine.git
    GIT_TAG master
)
FetchContent_MakeAvailable(TailsEngine)

add_executable(TestGame main.cpp)

target_link_libraries(TestGame PRIVATE TailsEngine)
```

> If you get errors in MSVC about runtime libraries, set your target's `MSVC_RUNTIME_LIBRARY` property to `"MultiThreaded$<$<CONFIG:Debug>:Debug>"`, like so:
> ```cmake
> set_property(TARGET <target> PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
> ```

`main.cpp`:
```cpp
#include <Tails/Engine.hpp>

int main()
{
    tails::CEngine engine;
    engine.run();
    return 0;
}
```
This will produce a blank window on your screen with an empty level.
