#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
// TODO - need these includes for it to compile for some reason??
#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

#include "Obj.h"

namespace tails
{
class AssetCache;
class Viewport;
}

namespace sf
{
class Transformable;
class Drawable;
class Text;
}

namespace tails
{
/**
 * \brief Acts like the Level class, but for widgets instead.
 *
 * If you are going to createWidget() as soon as possible, create() and display() are both viable. However, as
 * mentioned in their descriptions, create() requires "this" as the screen input, whereas display() does not.
 *
 * The Screen manages all of its "widgets". Instead of a widget being like an Entity and having its own functionality,
 * a widget is just controlled by the screen, with the screen telling what each widget should do
 *
 * Read the comment on Level class. This acts similarly. Loads a .json holding the UI layout, etc., and creates the
 * necessary widgets where and how on create() or display(). For each .json we want to load a UI layout for, we need
 * a new Screen class object. Maybe the Level could behave like this. But we only really want one level at a time. Hmm
 */
class Screen : public Object, public sf::Drawable
{
    friend Viewport;
    
public:
    std::vector<unique_ptr<sf::Drawable>> widgets;

    /**
     * \brief Creates a widget derived from sf::Drawable AND sf::Transformable. DOES NOT stored in a smart pointer.
     * Use createAndDisplayWidget() for that
     * \tparam WidgetT Must derive sf::Drawable AND sf::Transformable
     * \return Pointer to created widget
     */
    template<typename WidgetT>
    WidgetT* createWidget()
    {
        static_assert(std::is_base_of_v<sf::Drawable, WidgetT>, "Could not instantiate non-sf::Drawable widget");
        static_assert(std::is_base_of_v<sf::Transformable, WidgetT>, "Could not instantiate non-sf::Transformable widget");

        sf::Drawable* resultDrawable {new WidgetT};

        return dynamic_cast<WidgetT*>(resultDrawable);
    }

    /**
     * \brief Adds the input widget to the pending display widget vector, ready for it to start being drawn
     * and updated next frame
     * \param widgetToDisplay The widget to display and start being drawn
     */
    void displayWidget(sf::Drawable* widgetToDisplay);

    /**
     * \brief Creates AND displays a widget for next frame. Combination of both createWidget() and displayWidget().
     * This is the preferred way of displaying widgets unless you need to do stuff in between
     * \tparam WidgetT Must derive sf::Drawable AND sf::Transformable
     * \return Pointer to created widget
     */
    template<typename WidgetT>
    WidgetT* createAndDisplayWidget()
    {
        sf::Drawable* resultDrawable {createWidget<WidgetT>()};
        displayWidget(resultDrawable);
        return dynamic_cast<WidgetT*>(resultDrawable);
    }

protected:
    /**
     * \brief It is unsafe to call createWidget() without this as the input, as this screen is not yet added
     * to the screens vector in the Viewport.
     *
     * This might get changed so there are two vectors, one for the created screens and one for the displayed screens
     */
    virtual void create();
    /**
     * \brief Called when this screen is displayed to the screen (and added to the vector of screen in the Viewport).
     * It is safe to assume this object is now in that vector, so createWidget() doesn't need this as an input.
     */
    virtual void display();
    virtual void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    /**
     * \brief Called when this screen is being removed/destroyed. All members are still initialised however.
     * This is the first thing called in the destroy process
     */
    virtual void remove();

    void destroy() const;

    void setupData() override;
    void cleanupData() override;
    
    Viewport& getViewport() const;

    AssetCache& getAssetCache() const;
    
private:
    unique_ptr<AssetCache> m_assetCache;

    std::vector<unique_ptr<sf::Drawable>> m_widgetsPendingDisplay;

    sf::Text* m_fpsCounter;

    bool m_pendingRemoval {false};
};

}
