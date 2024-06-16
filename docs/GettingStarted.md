# Getting started
Create your own subclass of `Engine`. You can override `initCustomSubsystems()` to add your own subsystems via
`createSubsystem()`.

## Registry Subsystem
To add your own entities to be spawned from JSON, subclass the `EntityRegistry` class, and in its `init()` method,
call `assignRegistrar()` with the entity type as the template parameter, and the JSON name as the normal parameter.
Then, in your custom `RegistrySubsystem` class, in its `init()` method, add the entity registry using
`emplaceRegistry()`. Then, in your custom `Engine` class, override the `setupDefaultRegistrySubsystem()` method
and return an `std::unique_ptr` to your registry subsystem class.

The default `RegistrySubsystem` you derive from adds its own default `EntityRegistry` object, which you should leave and
allow it to do, because otherwise you cannot spawn engine entity classes from JSON. Basically, when you override
`init()`, call the parent `init()` before any of your own code.

## Custom States
You can set the default state the engine uses by overriding the `setupDefaultState()` method. Return an
`std::unique_ptr` to your state class. This custom state can then specify which layers to add, etc.

## engine.ini
This file is not required, however you should use one. It doesn't need to be named `engine.ini` or be in the
executable's root directory either, it just is those two by default. You can change these by setting the
`m_engineIniSource` variable in the `Engine` class. This points directly to the file.

The only requirement for this file is that it is in the `.ini` format (it does not explicitly need that extension,
however it must use that syntax within the file itself). The supported options (at the moment) are like so:
### paths
- data
- textures
- sounds
- fonts
- levels
- input
- saves
### render
- resolution
### window
- title
- size
- fullscreen
- vsync
- framerate limit

The default file looks like so:
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
resolution = 640, 480

[window]
title = Tails Engine
size = 640, 480
fullscreen = false
vsync = false
framerate limit = 0
```
It would make sense to copy and paste this into your own `engine.ini` and change the values as needed.