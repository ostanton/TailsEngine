# Engine Initialisation
> You can see the order of initialisation in the `Engine::initialise()` method.

The `Engine` class reads from `engine.ini` in the executable's root directory by default (this can be changed by
setting the `m_engineIniSource` member in the `Engine`'s constructor. It points straight to the file, so allows you
to rename the file also if you want). It then loads the settings from the file in `loadIni()` (which is overridable
if you wish to add your own settings), and sets whatever associated members it needs to (mainly the members in the
`Paths`, `RenderSettings`, and `WindowSettings` structs).

After the `engine.ini` (or whichever file you specified) is loaded, any user-defined custom subsystems are initialised.
> Note that this is not where a custom registry subsystem class should be initialised. Please override
> `Engine::setupDefaultRegistrySubsystem()` for that.

Once these are initialised, the engine's default subsystems are initialised, which includes the user's custom registry
subsystem if specified (or the default one if not). The order of default engine subsystem initialisation is as follows:
1. Asset Subsystem
2. Audio Subsystem
3. Registry Subsystem (user's or default)
4. Input Subsystem
5. State Subsystem

After the State Subsystem has initialised, it pushes the default state set via the virtual method
`Engine::setupDefaultState()`, which the user can override to return this own inherited State class. By default, the
method returns `nullptr`.

Once all the subsystems have initialised, the main SFML window is created, and the `Engine::run()` method can be
executed.