# Tails Engine

[Devlogs on the development of this engine](https://www.youtube.com/playlist?list=PL8y2eQUFF8A-a4O3URQ2i6lYfzapD0ouc).

The *Tails Engine* is a simple, 2D library intended to somewhat mimic the style of Gameboy Advance games. It uses C++, with SFML as the windowing, drawing, etc. library, and nlohmann's json library to read and write JSON. CMake is also used as a build system, with [CPM](https://github.com/cpm-cmake/CPM.cmake) to download the "packages". It is not at all production ready, and isn't intended to be used for anything large, or even anything outside my own personal uses, but you are free to use it for whatever, provided it falls within the bounds of the licenses of SFML, etc.

> Documentation and examples will be held in separate places. Documentation will be on the wiki part of this repository (when I get around to writing it), and examples will be in a separate repository.

- [Features](#features)
- [How to compile](#how-to-compile)
  - [Dependencies](#dependencies)
    - [Software](#software)
    - [Libraries](#libraries)
  - [Compilers](#compilers)
- [Integration (make a game with it!)](#integration)

## Features

- Locked internal resolution that maintains its aspect ratio (black bars!)
- Clearly named classes and structures (classes prefixed with 'C', structures prefixed with 'S', interfaces prefixed with 'I', etc.)
- "Context-specific" resource manager (per-level/any object) that owns its resources via `unique_ptr`s
- Input manager with support for keyboard, mouse, and Xbox controllers (currently only tested with an Xbox 1 controller)
- Class registry, allowing support of allocating a new object of the correct type just from a string ID value (generally just its class name as a string)

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

### Compilers

I mainly use MSVC and GCC to compile this project. MSVC because my main machine is running Windows, and GCC because the laptop I use to also work on this project is running Linux. Both compilers compile this project just fine.

I have tested with Clang, but it does not compile due to an issue with the standard library (I think). It would be nice if there was information online about it!

## Integration

It *should* work just fine if you download the repo via `FetchContent` or CPM, and just link against `TailsEngine`. I have not yet tested this, as I test the engine with a local project (with the engine added as a subdirectory of that project). I'm not amazing at CMake, but that just seems to work for me :)

For example (untested):

```cmake
cmake_minimum_required(VERSION 3.28.3)
project(TestGameProj)

# download CPM, look here (https://github.com/cpm-cmake/CPM.cmake/wiki/Downloading-CPM.cmake-in-CMake) or view CMakeLists.txt in TailsEngine root directory

CPMAddPackage("gh:ostanton/TailsEngine#master")

add_executable(TestGame main.cpp)

target_link_libraries(TestGame PRIVATE TailsEngine)
```

An example of a `main.cpp` could be:
```cpp
#include <Tails/Engine.hpp>

int main()
{
    tails::CEngine engine;
    engine.run();
    return 0;
}
```
This will produce a blank window on your screen with an empty, default, level.
