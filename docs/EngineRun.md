# Engine Run
Upon calling the `Engine::run()` method, the engine begins its main game loop, which runs until the main window is
closed (partial to change). Within this loop, the following happen in the specified order:
1. `Engine::preTick()` is called
2. The frame's clock timer is restarted
3. SFML window event polling occurs
4. `Engine::tick()` is called
5. `Engine::draw()` is called
6. `Engine::postTick()` is called

## `Engine::preTick()`
This method calls `Subsystem::preTick()` on all the engine's alive subsystems, and then checks if any subsystems are
`pendingCreate`. If they are, it sets them to not be `pendingCreate`.

## `Engine::tick()`
This method loops the alive subsystems, checking if they are `pendingCreate`. If they are not, `Subsystem::tick()` is
called.

## `Engine::draw()`
This method handles drawing to the window. It first clears the window contents, then checks if each alive subsystem is
`pendingCreate`, calling `sf::RenderWindow::draw()` with each subsystem as the input if they are not. After drawing
each subsystem, the window displays its contents.

## `Engine::postTick()`
This method calls `Subsystem::postTick()` on each alive subsystem. It then checks if each subsystem is `pendingDestroy`,
and if it is, it calls `Subsystem::deinit()` on it and erases it from the alive subsystems vector. If it is not
`pendingDestroy`, it skips this step.