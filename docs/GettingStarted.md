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