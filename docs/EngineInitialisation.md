# Engine Initialisation
The `Engine` class reads from `engine.ini` in the executable's root directory by default (this can be changed by
setting the `m_engineIniDirectory` member in the `Engine`'s constructor. It points straight to the file, so allows you
to rename the file also if you want). It then loads the settings from the file in `loadIni()` (which is overridable
if you wish to add your own settings), and sets whatever associated members it needs to (mainly the members in the
`Paths`, `RenderSettings`, and `WindowSettings` structs).