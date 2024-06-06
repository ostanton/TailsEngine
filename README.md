# Tails Engine
A simple, 2D, game engine in C++ and SFML. It focuses on the concept of states and layers. Only one state can be "active" at a time (the top one), but each state has any number of layers that can each be individually set to tick, draw, etc. The "GameState" may have a level layer and a screen (UI) layer for the HUD. The "PauseState" may then just have a screen layer, etc.

- [What it has](#what-it-has)
- [What is needed still](#what-is-needed-still)
- [How to compile](#how-to-compile)
- [Dependencies](#dependencies)
    - [Fetched with CMake](#fetched-with-cmake)
    - [Manually included](#manually-included)

## What it has
- Clear initialisation/deinitialisation of the engine
    - Engine subsystems (ManagerSubsystem, soon to have StateSubsystem, etc.)
- States
    - Level State
- State Stack
- Entities
    - RectEntity
- Extendable Engine class
- Extendable Managers
- State-specific camera/sf::View
- Event class that can hold delegates to class methods

## What is needed still
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
    - Pokemon
    - Moves
    - Levels?
    - Input actions & contexts
- Additional States
    - Widgets
        - Buttons
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
- Animated sprites
- Entity collision
    - Each entity has a `getGlobalBounds()` method? And/or a bool for `canCollide` or something. Need this optimised, only check collisions with entities near the current entity! CollisionManager??
- Tilemap stuff
- Audio manager for global sound + music playing
    - midi support
    - custom soundstream stuff
- Overlay states
    - A stack (or just plain vector since they overlay?) that draw over the main stack and tick independently.
    - Or scrap the whole stack idea and just go with a level class and separate widgets that have no bearing on the level?
    - If keeping with states, how would a HUD work? The level AND hud tick and draw, but then how do you stop them ticking (and maybe drawing) when opening the pause menu? Overlay states fix this? But how do you draw the pause menu over the HUD overlay? Remove the overlay? It doesn't seem very simple. Unless there's a separate Z ordering of layers??? Each state has layers? HUD and level go into one state, call it the GameState. PauseState is pushed, GameState no longer ticks or draws (maybe), and the PauseState is instead the one on top. So now we have the same state system but now states have a vector of layers. States can then be derived from? So users can create their own PauseState, GameState, etc.? What would the type of the vector be? StateLayer? UI screens and levels would need to derive from that then! Users can then make their own layers by deriving StateLayer!
- Engine default settings struct
    - User either subclasses or creates an object from it, sets the object types via template parameters (class template so they can both derive and/or instance it?) and pass that into the engine init method?
    - Would require a base Settings struct, so the templated class one derives it and the engine just has a pointer to the base one!
- Screenshot ability?
    - RenderWindow::capture() - returns an sf::Image, save it to file in save/captures/? SFML docs says it's deprecated and instead to update a texture with the window as input!
- GameSettings.ini
    - settings file for game-specific settings, like audio volume, maybe resolution/window size?, fullscreen, etc.
- Whenever modules are fully supported (could be never lol!) move to that C++ version and move to them. Much faster compilations!

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

# Input pseudocode
```
struct InputValue final
{
    variant<bool, float> value;

    template<typename T>
    T getValue()
    {
        return std::get<T>(value);
    }

    template<typename T>
    bool isValueType()
    {
        return std::holds_alternative<T>(value);
    }
}

enum class ActionTrigger
{
    Started, // once immediately when active
    Triggered, // every frame while key is active
    Completed // once immediately when no longer active
}

// contains bindings, friendly name, etc. for a given action
struct InputAction final
{
    std::string name;
    unordered_map<ActionTrigger, vector<function<void(InputValue)>>> delegateMap; // lambda-wrapped functions
    unordered_map<ActionTrigger, vector<unique_ptr<InputFunc>> funcMap; // any kind of function, given it has an addFunc() method and associated class derived from InputFunc

    void addFunction(ActionTrigger trigger, function<void(InputValue)> func)
    {
        delegateMap[trigger].push_back(func);
    }

    void execute(ActionTrigger trigger, InputValue value)
    {
        for (auto& func : delegateMap[trigger])
        {
            func(value);
        }
    }

    // add object member function
    template<typename C>
    void addFunc(ActionTrigger trigger, void(C::*function)(InputValue), C* object)
    {
        funcMap[trigger].push_back(make_unique<InputMemberFunc<C>>(function, object));
    }

    void execute(ActionTrigger trigger, InputValue value)
    {
        for (auto& funcObj : funcMap[trigger])
        {
            funcObj->execute(value);
        }
    }
}

struct InputFunc
{
    virtual ~InputFunc() = default;
    virtual void execute(InputValue value) = 0;
}

// C for class
template<typename C>
struct InputMemberFunc final : InputFunc
{
    InputMemberFunc() = default;
    InputMemberFunc(void(C::*function)(InputValue), C* object)
        : m_function(function), m_object(object) {}

    void execute(InputValue value) override
    {
        (m_object->*m_function)(value);
    }

private:
    void(C::*m_function)(InputValue);
    C* m_object;
}

// holds any kind of input, plus helper functions
struct Key final
{
    variant<sf::Keyboard, sf::Joystick, sf::Mouse> value;
    variant<bool, float> currentState; // ??

    bool isKeyboardPressed()
    {
        return sf::Keyboard::isKeyPressed(std::get<sf::Keyboard>(value));
    }

    bool isKeyDown()
    {
        return isKeyboardPressed() || isJoystickActive() || isMousePressed();
    }
}

struct InputModifier
{
    virtual bool allowInput(InputValue value) = 0;
    virtual InputValue tick(float deltaTime, InputValue value) = 0;
}

struct DeadzoneModifier
{
    DeadzoneModifier() = default;
    DeadzoneModifier(float inDeadzone)
        : deadzone(inDeadzone) {}

    float deadzone {0.1f};

    bool allowInput(InputValue value) override
    {
        return value.getValue<float>() >= deadzone;
    }

    InputValue tick(float deltaTIme, InputValue value) override
    {
        if (value.isValueType<float>())
        {
            if (value.getValue<float>() >= deadzone) return value;
            return InputValue(0.f);
        }
        else
        {
            return value;
        }
    }
}

// bad name but describes when an action is to be executed
struct InputMappingData final
{
    Key key;
    vector<unique_ptr<InputModifier>> modifiers;

    template<typename T, typename... ArgsT>
    void createModifier(ArgsT&&... args)
    {
        modifiers.push_back(make_unique<T>(std::forward<ArgsT>(args)...));
    }
}

// maps actions to SFML keys. Used to call the correct action when a key is pressed, etc.
// controlled via higher input manager
class InputMappingContext final
{
    unordered_map<string, pair<InputAction, vector<InputMappingData>>> mappings; // make pair into struct instead?

public:
    InputAction& getAction(const string& id)
    {
        return mappings[id].first;
    }

    // might need pretick and posttick if there's anything needed to do before/after a frame, like reset states, etc.
    void tick()
    {
        // for each input action
        for (auto& pair : mappings) // type: std::pair<InputAction, vector<InputMappingData>>
        {
            InputValue inputValue;
            bool allowInput = true;

            // for each mapping data
            for (auto& mappingData : pair.second) // type: InputMappingData
            {
                if (mappingData->key.isKeyboardPressed())
                {
                    inputValue.value = true;

                    // for each input modifier
                    for (auto& modifier : mappingData.modifiers)
                    {
                        if (!modifier->allowInput(value))
                        {
                            allowInput = false;
                            break;
                        }
                    }
                }
                else if (mappingData->key.isJoystickActive())
                {
                    inputValue.value = key.joystickValue();
                }
            }

            // only execute function if modifiers allow it
            if (allowInput) pair.first.execute(ActionTrigger::Triggered, inputValue);
        }
    }
}

class InputManager
{
    unordered_map<string, unique_ptr<InputMappingContext>> activeContexts; // string key is set from json name/context key kinda thing

public:
    void tick(float deltaTime)
    {
        for (auto& contextPair : activeContexts)
        {
            contextPair.second->tick(deltaTime);
        }
    }

    template<typename T>
    void addContext(const string& id)
    {
        activeContexts[id] = make_unique<T>();
    }

    void addContext(const string& id, unique_ptr<InputMappingContext> context)
    {
        activeContexts[id] = move(context);
    }

    template<typename C>
    void addBinding(const string& context, const string& action, ActionTrigger trigger, void(C::*function)(InputValue), C* object)
    {
        activeContexts[context]->mappings[action].first.addFunc<C>(trigger, function, object);
    }

    InputMappingContext& getContext(const string& id)
    {
        return *activeContexts[id];
    }

    InputAction& getAction(const string& context, const string& action)
    {
        return getContext(context).getAction(action);
    }
}
```

# Input mapping data
View `actions.json` and `contexts.json`.

# Asset Metadata
## Asset types
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
