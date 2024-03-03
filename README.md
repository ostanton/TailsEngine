<img align="right" src="Assets/Textures/Tails.png">

# Tails Engine
The Tails Engine is a simple 2D, [SFML](https://www.sfml-dev.org/ "SFML Homepage")-based game engine I'm developing in my free time. Its purpose is to both teach me more about C++ programming, but also to serve as a kind of retro games engine, mainly the [GBA](https://en.wikipedia.org/wiki/Game_Boy_Advance "GBA Wikipedia Page").
The idea came about when I got the idea to make a Sonic fangame. I looked around for code-focused 2D C++ game engines, and it seems everyone just points to SFML and doing it yourself. So I did.
I looked at [Tilengine](https://www.tilengine.org/ "Tilengine Homepage") for a while, but with it being in C, I decided to pass on it. It looks phenomenal however, just not the kind of workflow for me.
I also looked at [butano](https://github.com/GValiente/butano "butano's GitHub") and just developing straight for the GBA. It's a really cool environment to work in, but I don't think I'm quite there yet in terms of skill level. That and the fact there's like 2 tutorials. The documentation can only get so far when wanting to see how the library actually works and what the best practices are, etc.

I've designed this engine with the SFML standards in mind, or what I could tell are their standards anyway. Most things are commented so should be easy to know what method does what, etc.
The architecture is kind of similar to [Unreal Engine](https://www.unrealengine.com/en-US "Unreal Engine Homepage"), which is mainly due to the fact I look at its source code a lot and am super used to it. Lots of decisions about the architecture were made because I wanted it to be simple though, so there's no "components", etc. in Actors and such. Just plain entities which can hold whatever you want.

Setup instructions to come.

And don't worry about the rider stuff, .sln file, etc. I'll clean up the repo later when it's more polished.

# Features:
- Asset Caches (load an asset once and reuse it, caches are local to their context)
- Input Manager (set up action and key bindings)
- Basic Entity collision
- Entities (limited, they are derived from sf::Sprite currently)
- Simple GUI layer (`Screen`s composed of `sf::Drawable`s)

# Future Additions:
- Getting sf::Views working
- LDTK map format for levels
- Load UI layouts from JSON
- More robust collision system

# Dependencies
- [SFML](https://www.sfml-dev.org/ "SFML Homepage")
