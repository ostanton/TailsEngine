# Tails Engine

This engine is in a rewrite!
[Devlogs on the rewrite of this engine.](https://www.youtube.com/playlist?list=PL8y2eQUFF8A-a4O3URQ2i6lYfzapD0ouc)

Beyond the description section is the previous target stuff for this engine. For now, I want this engine to be more like a "retro" game engine, specifically containing simple architecture and producing results akin to that of a Gameboy Advance and similar. The idea is this:
- Games made using Tails Engine will be mostly scripted with [AngelScript](https://www.angelcode.com/angelscript/), similar to Unreal Engine and Blueprints.
- The game will render at a fixed resolution that can be "upscaled" to fix the window size.
- Simple implementations of everything. Like managing assets, an "AssetHandle" is just a `size_t`, an "AssetInfo" object is just a container for the raw data with some extra information and the ability to load and unload that raw data, etc. Even that is probably overkill however (you only really need a way for multiple sprites to reference one texture, that's the bare minimum. loading & unloading on the fly doesn't really add anything, as if a sprite exists, it will use the specified texture. If it does not exist, either the texture also does not exist, or something else using the texture exists. `shared_ptr` stuff probably idk).
- Input is only as complicated as it is because I wanted to conquer the challenge of making it work. I will strip it back probably to the barebones of:
  - Actions with mapped keys
  - When action is active, changes state, etc., call bound function
  - Contexts (like the idea of them in Unreal) will cease to exist. A game will have a list of "actions" and the keys bound to those actions, and that is is. No dynamic adding and rmoving. This is to emulate a Gameboy (for example) having a set amount of buttons that are usable. Keys can just be bound to the actions for user-friendlyness, etc.
- Delegates and events will still exist. They are QoL things that just help so much, why remove them? (That being said I might make a separate delegate library for them also.)
- Outers may not exist anymore, instead favouring a global `Engine` pointer or something. Stripping this back to where the base `Object` class isn't even needed would be nice.

## Description
A simple, 2D, game engine in C++ and SFML. It focuses on the concept of states and layers. Only one state can be "active" at a time (the top one), but each state has any number of layers that can each be individually set to tick, draw, etc. The "GameState" may have a level layer and a screen (UI) layer for the HUD. The "PauseState" may then just have a screen layer, etc.

> Examples and docs are being separated from this repository into their own, or just elsewhere. Their links will be here when they do end up in that elsewhere.

- [What it has](#what-it-has)
- [What is needed still](#what-is-needed-still)
- [How to compile](#how-to-build--compile)
- [Dependencies](#dependencies)
- [Integration](#integration)

## What it has
- Clear initialisation/deinitialisation of the engine
    - Engine subsystems (AssetSubsystem, InputSubsystem, LayerSubsystem, etc.)
- States
    - Level State
- State Stack
- Entities
    - RectEntity
- Extendable Engine class
- Extendable Managers
- State-specific camera/sf::View
- Event class that can hold delegates to class methods
- All deferred actions like adding or removing items from vector during a tick will be "finalised" at the end of that same frame, or at the start of the next frame, depending on what it is. By finalised I mean adding an item, that item will only start ticking and drawing, etc. after the start of the next frame. When removing an item, it gets erased at the end of that same frame. Start and end lifetime methods (like added, removed, spawn, despawn, etc.) are called at the start and end of the frame respectively once the item has been finalised.

## Next features
The things I want to implement ASAP, basically:
- Entity collision
- Input mapping

## What is needed still
- Regarding "finalisation", I think the spawn, etc. methods should happen at the start of the next frame, but the despawn, etc. methods should happen immediately as they are called. Calling them at the end of the frame allows for the possibility of a pointer in one class to be null (as it has been deleted) when it should be valid.
- Create default folders and files in same directory as executable if they do not already exist
    - engine.ini
    - save
        - no default data (how should saves be handled??)
    - res
        - tex
        - sound
        - level
        - font
        - data
            - input
    - The only file that is created is `engine.ini`. The rest are empty directories to be filled based on the game's requirements.
- Default game icon. Path will be stored somewhere that is overridable (does it need to be? Not really. Unreal's built icon is called `Application.ico`, and you can't change that I don't think. No it does not matter if you can change it, why put the effort in to make is customisable if no one uses it or needs it?), but by default it's either next to the executable, or in `res/tex/`, by default called `icon.png` or something.
    - It will probably be in the root of `res/tex/` and be called `icon.png`. That's pretty much final.
- Input Mappings
    - I'm now thinking this solution is a bit too complicated for this engine. I think maybe something simpler is in order? I still want delegates, events and function binding though.
- Input stack? Probably accidental pushing two buttons on the same frame, if that is even a problem!?
- Load JSON
    - Levels?
    - Input actions & contexts
- Additional States
    - Widgets
        - Buttons
            - Some form of brush struct? Like the texture, rect to draw the texture in, 9-slice, etc.?
            - Focus support (keyboard & gamepad navigation)
                - NavigationConfig class/struct? Defines which input mappings call each navigation, each navigation being an enum like in Unreal?
            - Mouse support
        - Text
        - Text Field
        - Containers:
            - Scroll box
            - Vertical/Horizontal stack box
            - Canvas
        - Gradient effects with vertex colours?
- Entity collision
    - Each entity has a `getGlobalBounds()` method? And/or a bool for `canCollide` or something. Need this optimised, only check collisions with entities near the current entity! CollisionManager??
- Tilemap stuff
- Audio manager for global sound + music playing
    - midi support
    - custom soundstream stuff
- Screenshot ability?
    - RenderWindow::capture() - returns an sf::Image, save it to file in save/captures/? SFML docs says it's deprecated and instead to update a texture with the window as input!
- GameSettings.ini
    - settings file for game-specific settings, like audio volume, maybe resolution/window size?, fullscreen, etc.
    - user would set what settings should be set here! So not default in engine then? Or default is window things and maybe audio things?
- Whenever modules are fully supported (could be never lol!) move to that C++ version and move to them. Much faster compilations!
- Better CMake support so it's easy to include or fetch it in another CMake project

## How to build & compile
```
mkdir build
cd build
cmake ..
make
```

## Dependencies
This project uses C++20 features and requires CMake version 3.25.1 or above. All libraries are automatically downloaded and built via [CPM](https://github.com/cpm-cmake/CPM.cmake).
- [SFML 2.6.1](https://www.sfml-dev.org/)
  - And thus [OpenAL](https://openal-soft.org/) (download the binaries [here](https://openal-soft.org/openal-binaries/)).
- [nlohmann/json](https://github.com/nlohmann/json)
- [metayeti/mINI](https://github.com/metayeti/mINI)

## Integration
A simple example CMakeLists.txt could be as follows:
```cmake
cmake_minimum_required(VERSION 3.25.1)

project(TestTailsGame LANGUAGES CXX)

# Download CPM.cmake
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.0/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

add_executable(TailsGame main.cpp)

# Use CPM to add the TailsEngine package
CPMAddPackage("gh:ostanton/TailsEngine@0.0.2")

target_link_libraries(TailsGame PRIVATE TailsEngine)
```
## Binary folder
The game expects an `engine.ini` file next to the executable. This is where paths to textures, sounds, etc. are set, in addition to window settings and render settings. Some of these might move to a separate `user_settings.ini` file in the future. For now though, it's all in the `engine.ini` file.
The structure by default is as follows:
```
- res
    - data
        - input
            - actions.json, contexts.json, etc. (describe the input actions and the keys they are mapped to)
        - items.json, etc. (game-specific general data, weapons.json for example)
    - font
    - level
    - sound
    - tex
- save
    - where all the saves are stored
- engine.ini
```
The `engine.ini` contents by default is as follows (you can copy and paste for a game using this library to work properly):
> A trailing forward-slash is added by the engine. This means that when opening a file via path, you only need to enter
the file name and whatever path variable to use instead of adding a forward-slash in front of the file name. The
library used to load .ini files does not like forward-slashes at the end of non-literal strings for some reason. So
just treat these as specifying the folder name instead of full directory!
```ini
[paths]
data = res/data
textures = res/tex
sounds = res/sound
fonts = res/font
levels = res/level
input = res/data/input
saves = save

[render]
resolution_x = 640
resolution_y = 480

[window]
title = Tails Engine
size_x = 640
size_y = 480
fullscreen = false
vsync = false
framerate_limit = 0

[contexts]
player = player.json
```
> `[contexts]` is for input action mappings.
Without this file, the engine cannot initialise or really do anything, as it relies on those paths being set, and the render and window sections have valid fields and values (for the window to be initialised).

## Asset Metadata
### Asset types
- sprite
- spritesheet
- tilemap (requires tile width & height, not necessarily columns and rows, as those can be worked out via the tile size and texture size)
- music
- sound
- font

> Only spritesheets "require" metadata, for the animations. It is optional for everything else, to cut down on file count. Therefore, any function that takes in a path to a .png for example also should be able to take in a path to a metadata .json. Maybe there will be things like `loadSpriteSheet()` which only allows a path to the metadata, etc. But generally both functions is preferrable. The metadata generally would just link to the source asset anyway. If an asset does not have an associated `.json` of the same name, it will be created with sensible defaults, like music always looping, having 1 volume and pitch, etc.

```json
{
    "type": "spritesheet",
    "source": "playersheet.png",
    "animations": {
        "idle": {
            "speed": 1,
            "initial-frame": 0,
            "frames" [
                {
                    "x": 0,
                    "y": 0,
                    "w": 16,
                    "h": 16,
                    "speed": 1
                },
                {
                    "x": 16,
                    "y": 0,
                    "w": 16,
                    "h": 16,
                    "speed": 1
                }
            ]
        },
        "walk": {
            "speed": 1,
            "initial-frame": 0,
            "frames": [
                {
                    "x": 0,
                    "y": 16,
                    "w": 16,
                    "h": 16,
                    "speed": 1
                }
            ]
        }
    }
}

{
    "type": "tilemap",
    "source": "veridiancity.png",
    "tilew": 16,
    "tileh": 16,
    "cols": 4,
    "rows": 5
}
```
