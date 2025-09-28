# Tails Engine

This is a rather simple, and very incomplete, 2D game "engine". It uses SDL3, and aims to run on all the platforms SDL3 supports.
You can think of it almost like a game-focused wrapper for SDL more than its own thing, as it relies on SDL a lot.

>It is very early in development, with many things being either unimplemented, broken, or mid-refactor. Have a look if you dare, but don't expect much!

- [Dependencies](#dependencies)
- [Compilers](#compilers)
- [Platforms](#platforms)
- [How to use](#how-to-use)

## Dependencies

Dependent libraries (SDL3, etc.) are downloaded automatically via CMake's FetchContent (or Zig's build system if you are using that) if not already available.

- C++20
- [CMake](https://cmake.org/) or [Zig](https://ziglang.org/)
- [SDL3](https://libsdl.org/)

## Compilers

I mainly use MSVC because I develop on Windows, however I do use GCC for PSP builds and Clang for Zig builds.
All three of those compilers should work fine.

## Platforms

Since Tails uses SDL3, it more or less supports all the platforms SDL3 supports. However, these are the platforms I know work:
- Windows
- Linux (Ubuntu and Arch)
- PSP (native & emulator)

## How to use

### CMake

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

### Zig

Requires Zig 0.15.1, and it is still early on and WIP, so don't rely on it, but:

```
zig fetch --save git+https://github.com/ostanton/TailsEngine
```

```zig
// build.zig
const tails_dep = b.dependency("tails", .{
    .target = target,
    .optimize = optimize,
    // etc.
});
exe.root_module.linkLibrary(tails_dep.artifact("tails"));
```

### `main.cpp`

A minimal `main.cpp` is like so:

```cpp
#include <Tails/Application.hpp>

int main(int argc, char* argv[])
{
    using namespace tails;
    app::init(argc, argv);
    app::run();
    app::deinit();
    return 0;
}
```

Each of these application functions are more or less just a wrapper around calling various subsystem functions of the same name.
So if you want to insert your own subsystem between default engine subsystems, just disect whatever function you need in main.

For a more in-depth example, see the [example](example/) folder.
