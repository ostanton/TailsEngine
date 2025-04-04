# Tails Engine

This is a rather simple, and very incomplete, 2D game "engine". It uses SDL3, and aims to run on all the platforms SDL3 supports.
You can think of it almost like a game-focused wrapper for SDL more than its own thing, as it relies on SDL a lot.

>It is very early in development, with many things being either unimplemented, broken, or mid-refactor. Have a look if you dare, but don't expect much!

- [Dependencies](#dependencies)
- [Compilers](#compilers)
- [Platforms](#platforms)
- [How to use](#how-to-use)

## Dependencies

Dependent libraries (SDL3, etc.) are downloaded automatically via CMake's FetchContent if not already available.

- C++17
- [CMake](https://cmake.org/)
- [SDL3](https://libsdl.org/)

## Compilers

I personally use MSVC and GCC for Windows and Linux compilation respectively. I don't know if other compilers will work out the box.

## Platforms

Since Tails uses SDL3, it more or less supports all the platforms SDL3 supports. However, these are the platforms I know work:
- Windows
- Linux (Ubuntu)
- PSP (native & emulator)

## How to use

A simple FetchContent in CMake to this repo and then linking it should suffice. Something akin to:

```cmake
cmake_minimum_required(VERSION 3.24)
project(MyGame)

include(FetchContent)
FetchContent_Declare(
    Tails
    GIT_REPOSITORY https://github.com/ostanton/TailsEngine.git
    GIT_TAG master
)
FetchContent_MakeAvailable(Tails)

add_executable(MyGame main.cpp)
target_link_libraries(MyGame PRIVATE ostanton::Tails)
```

The `main.cpp` must then declare what application subclass to use, like so:

```cpp
#include <Tails/Application.hpp>
#include <Tails/EntryPoint.hpp>

class CMyApp : public tails::IApplication
{
public:
    CMyApp()
        : IApplication({1280, 720})
    {}

private:
    void onInputEvent(const tails::CEvent& ev) override
    {
        if (ev.is<tails::CEvent::SClosed>())
            exit();
    }
};

TAILS_IMPLEMENT_ENTRY_POINT(CMyApp, "My Game!")
```

For a more in-depth example, see the [example](example/) folder.
