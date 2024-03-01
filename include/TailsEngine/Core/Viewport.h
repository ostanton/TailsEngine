#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "Obj.h"
#include "Screen.h"

namespace tails
{
class InputManager;
class ResourceManager;
class ApplicationWindow;
class Widget;
}

namespace sf
{
class Clock;
class View;
}

namespace tails
{
/**
 * \brief This handles widgets and UI through its own sf::View, handled via the tails::ApplicationWindow. Basically
 * the "World" of widgets, holing "Level"s (screens).
 *
 * I'm thinking there might in the future be separate layers for each specific class (a layer for sf::Text, a layer
 * for sf::Shape, a layer for sf::Sprite, etc.)
 *
 * Widgets do not update(), but the Viewport and Screens do, allowing for input
 */
class Viewport : public Object, public sf::Drawable
{
    friend ApplicationWindow;
    
public:
    Viewport();

    unique_ptr<sf::Clock> clock;
    sf::Time frameTime;

protected:
    /**
     * \brief Called in postInitialise of ApplicationWindow
     */
    void create();
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    unique_ptr<sf::View> widgetView;

    // TODO - Abstract this into WidgetTree class?

    template<typename WidgetT>
    WidgetT* createWidget()
    {
        return createWidget<WidgetT>(getTopMostScreen());
    }

    /**
     * \brief Creates a widget in the desired screen for use and drawing
     * \tparam WidgetT Widget type to create
     * \param targetScreen Screen to create the widget in
     * \return Pointer to the created widget object
     */
    template<typename WidgetT>
    WidgetT* createWidget(Screen* targetScreen)
    {
        sf::Drawable* resultDrawable { newObject<WidgetT>(this) };

        targetScreen->widgets.emplace_back(resultDrawable);

        return dynamic_cast<WidgetT*>(resultDrawable);
    }

    /**
     * \brief Creates and loads a screen. It will be drawn on the next frame
     * \tparam ScreenT The screen type to create and display
     * \return Pointer to the created screen object
     */
    template<typename ScreenT>
    ScreenT* createAndDisplayScreen()
    {
        auto resultScreen = createScreen<ScreenT>();
        displayScreen(resultScreen);

        return dynamic_cast<ScreenT*>(resultScreen);
    }

    /**
     * \brief Displays a screen object within the viewport
     * \param screenToDisplay The screen object to display
     */
    void displayScreen(Screen* screenToDisplay);

    /**
     * \brief Creates a screen. Should favour createAndDisplayScreen unless you need to setup beforehand.
     * createAndDisplayScreen stores the created pointer into a smart pointer immediately. This method uses no
     * smart pointer, so it is your responsibility to prevent leaks
     * \tparam ScreenT The screen type to create
     * \return Pointer to the created screen object
     */
    template<typename ScreenT>
    ScreenT* createScreen()
    {
        Screen* resultScreen { newObject<Screen>(this) };

        resultScreen->create();
        
        return dynamic_cast<ScreenT*>(resultScreen);
    }

    /**
     * \brief Destroy a screen (and delete its memory)
     * \param screenToDestroy Screen to destroy
     * \return If we successfully destroyed the input screen
     */
    bool destroyScreen(const Screen* screenToDestroy);
    
    std::vector<unique_ptr<Screen>> screens;

    std::vector<Screen*> getScreensRaw() const;

    Screen* getTopMostScreen() const;
};

}
