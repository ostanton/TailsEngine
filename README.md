<img align="right" src="src/Assets/Textures/Tails.png">

# Tails Engine
The Tails Engine is a simple 2D, SFML-based game engine I'm developing in my free time. Its purpose is to both teach me more about C++ programming, but also to serve as a kind of retro games engine, mainly the GBA.
The idea came about when I got the idea to make a Sonic fangame. I looked around for code-focused 2D C++ game engines, and it seems everyone just points to SFML and doing it yourself. So I did.
I looked at Tilengine for a while, but with it being in C, I decided to pass on it. It looks phenomenal however, just now the kind of workflow for me.
I also looked at butano and just developing straight for the GBA. It's a really cool environment to work in, but I don't think I'm quite there yet in terms of skill level. That and the fact there's like 2 tutorials. The documentation can only get so far when wanting to see how the library actually works and what the best practices are, etc.

I've designed this engine with the SFML standards in mind, or what I could tell are their standards anyway. Most things are commented so should be easy to know what method does what, etc.

Setup instructions to come.

# Features:
- Resource Manager (load an asset once and reuse it)
- Input Manager (set up action and key bindings)
- Basic Entity collision
- Entities (limited, they are derived from sf::Sprite currently)

# Future Additions:
- Getting sf::Views working
- Full (if simple) GUI layer
- More complex collision handling
