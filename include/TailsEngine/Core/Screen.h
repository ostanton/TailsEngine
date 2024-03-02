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
class TextWidget;
class Viewport;
}

namespace sf
{
class Drawable;
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
 */
class Screen : public Object, public sf::Drawable
{
    friend Viewport;
    
public:
    std::vector<unique_ptr<sf::Drawable>> widgets;

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
    
    Viewport& getViewport() const;

    AssetCache& getAssetCache() const;
    
private:
    unique_ptr<AssetCache> m_assetCache;
};

}
