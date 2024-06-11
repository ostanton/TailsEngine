# Tails Engine
A simple, 2D, game engine in C++ and SFML. It focuses on the concept of states and layers. Only one state can be "active" at a time (the top one), but each state has any number of layers that can each be individually set to tick, draw, etc. The "GameState" may have a level layer and a screen (UI) layer for the HUD. The "PauseState" may then just have a screen layer, etc.

> Word of note (and caution): This library is primarily tested on a not-so-powerful laptop running Debian. I run it on Windows 11 occasionally, although chances are if you build via a Visual Studio solution, it might not link properly (I know from experience). I'm not amazingly well-versed in CMake or building in general, so these problems unfortunately either won't get sorted, or will be very far down on my priority list.

> Another note, this is my biggest project to date (sort of, diregarding Unreal games), and I am learning many new things along the way. This is all to say that the code in this library is probably quite sub-par, and the CMakeLists.txt definitely isn't as good as it could be. This is mainly a project just for me, so I have a simple engine I know how to use for 2D games I want to make in the future (since I either suck at searching for them, or there's a lack of proper object-oriented, simple, 2D game engines/frameworks).

- [What it has](#what-it-has)
- [What is needed still](#what-is-needed-still)
- [How to compile](#how-to-compile)
- [Dependencies](#dependencies)
    - [Fetched with CMake](#fetched-with-cmake)
    - [Manually included](#manually-included)

## What it has
- Clear initialisation/deinitialisation of the engine
    - Engine subsystems (AssetSubsystem, InputSubsystem, StateSubsystem, etc.)
- States
    - Layers
        - LevelLayer
        - ScreenLayer
- Entities
    - Rect Entity
    - Animated Sprite Entity
- Extendable Engine class
- Extendable Managers
- State-specific camera/sf::View
- Event class that can hold delegates to class methods
- All deferred actions like adding or removing items from vector during a tick will be "finalised" at the end of that same frame, or at the start of the next frame, depending on what it is. By finalised I mean adding an item, that item will only start ticking and drawing, etc. after the start of the next frame. When removing an item, it gets erased at the end of that same frame. Start and end lifetime methods (like added, removed, spawn, despawn, etc.) are called at the start and end of the frame respectively once the item has been finalised.

## What is needed still
- Create default folders and files in same directory as executable if they do not already exist (doing this at game runtime probably isn't the way to go. Easy to to make those folders, etc. when starting a new project? Template one maybe?)
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
    - Scroll down for implementation test
- Input stack? Probably accidental pushing two buttons on the same frame, if that is even a problem!?
- Asset Manager/Cache
    - Global or context-sensitive? One in each State?
    - Asset metadata (scroll past Input code)
- Load JSON
    - Base JsonLoader (get a better name bruh) class with:
        - JsonLoader* load(Json& obj) - covariant return
        - maybe std::string getName()
        - load is called when the object is being spawned or cloned. There is no clone method. When overriding load(), classes should allocate a new object of said class on the heap, set their default members from the json object, then return the pointer to it.
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
- Registry base class
    - Child templated class with further children like EntityRegistry, InputModifierRegistry, WidgetRegistry, etc.
- Entity collision
    - Each entity has a `getGlobalBounds()` method? And/or a bool for `canCollide` or something. Need this optimised, only check collisions with entities near the current entity! CollisionManager??
- Tilemap stuff
- Audio manager for global sound + music playing
    - midi support
    - custom soundstream stuff
- Engine default settings struct
    - User either subclasses or creates an object from it, sets the object types via template parameters (class template so they can both derive and/or instance it?) and pass that into the engine init method?
    - Would require a base Settings struct, so the templated class one derives it and the engine just has a pointer to the base one!
    - Would be used to set default registries, maybe GameMode or something if going down the Unreal-style path, etc.
- Screenshot ability?
    - RenderWindow::capture() - returns an sf::Image, save it to file in `save/captures`? SFML docs says it's deprecated and instead to update a texture with the window as input!
- GameSettings.ini
    - settings file for game-specific settings, like audio volume, maybe resolution/window size?, fullscreen, etc.
- Whenever modules are fully supported (could be never lol!) move to that C++ version and move to them. Much faster compilations!
- Specialised SubsystemManager class so it's easy for any class to have subsystems (problems I have so far is Tickable class and virtual inheritance stuff!)
- Better CMake support so it's easy to include or fetch it in another CMake project

## How to compile
```
mkdir build
cd build
cmake ..
make
```

## Dependencies
### Fetched with CMake
These libraries are automatically downloaded and added and built when running CMake.
- [SFML](https://www.sfml-dev.org/)
- [nlohmann/json](https://github.com/nlohmann/json)
### Manually included
These libraries are not downloaded with CMake, but are found in their respective folders in `include/`.
- [LeksysINI](https://github.com/Lek-sys/LeksysINI)

## Binary folder
The game expects an `engine.ini` file next to the executable. This is where paths to textures, sounds, etc. are set, in addition to window settings and render settings. Some of these might move to a separate `user_settings.ini` file in the future. For now though, it's all in the `engine.ini` file.
The structure by default is as follows (in the same folder as the built executable):
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
- Windows DLLs (because they are oh so very annoying!)

The `engine.ini` contents by default is as follows (you can copy and paste for a game using this library to work properly):
```
[paths]
data = res/data
textures = res/tex
sounds = res/sound
fonts = res/font
levels = res/level
input = res/data/input
saves = save

[render]
resolution = 640, 480

[window]
title = Tails Engine
size = 640, 480
fullscreen = false
```

Without this file, the engine cannot initialise or really do anything, as it relies on those paths being set, and the render and window sections have valid fields and values (for the window to be initialised).

## Classes (alphabetical order)
> This isn't really being updated. When the engine is more mature I will add all this to a wiki.
- Debug
- Engine
- Object
- Tickable
### Assets
- Asset Handle
- Asset Info
- Resource
    - Font Resource
    - Sound Resource
    - Texture Resource
### Entities
- Entity
    - Rect Entity
    - Sprite Entity
### Events
- Delegate
    - Method Delegate
- Event
- Multi Event
### Input
- Input Action
- Input Context
- Input Modifier
- Input Value
### Layers
- Layer
### Registries
- Registry
### States
- State
### Subsystems
- Subsystem
    - Asset Subsystem
    - Audio Subsystem
    - Registry Subsystem
    - Input Subsystem
    - State Subsystem
### UI
- Slot
- Widget

## Asset Metadata
### Asset types
- sprite
- spritesheet
- tilemap (requires tile width & height, not necessarily columns and rows, as those can be worked out via the tile size and texture size)
- music
- sound
- font

> Only spritesheets "require" metadata, for the animations. It is optional for everything else, to cut down on file count. Therefore, any function that takes in a path to a .png for example also should be able to take in a path to a metadata .json. Maybe there will be things like `loadSpriteSheet()` which only allows a path to the metadata, etc. But generally both functions is preferrable. The metadata generally would just link to the source asset anyway. If an asset does not have an associated `.json` of the same name, it will be created with sensible defaults, like music always looping, having 1 volume and pitch, etc.

```
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
