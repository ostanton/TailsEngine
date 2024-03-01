#include "TailsEngine/Core/TestScreen.h"

#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/ResourceManager.h"
#include "TailsEngine/Widgets/RectWidget.h"
#include "TailsEngine/Widgets/TextWidget.h"

void tails::TestScreen::display()
{
    getResourceManager().loadFont("main_font", "Assets/Fonts/PixelOperatorMono.ttf");
    m_textWidget = getViewport().createWidget<TextWidget>(this);
    m_textWidget->setFont(getResourceManager().fontManager.getAssetRef("main_font"));
    
    getViewport().createWidget<RectWidget>(this)->setPosition(400.f, 400.f);
}

void tails::TestScreen::update(float deltaTime)
{
    m_textWidget->setString("FPS: " + std::to_string(static_cast<unsigned long long>(1.f / deltaTime)));
    
    if (getInputManager().onActionPress("l"))
    {
        destroy();
    }
}
