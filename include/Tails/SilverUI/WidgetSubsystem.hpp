#ifndef TAILS_WIDGET_SUBSYSTEM_HPP
#define TAILS_WIDGET_SUBSYSTEM_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails
{
    class SWidget;
    class ISlot;
    class IRenderer;
    class CEvent;
}

namespace tails::ui
{
    TAILS_API void init();
    TAILS_API void processEvent(const CEvent& ev);
    TAILS_API void tick(float deltaSeconds);
    TAILS_API void render(IRenderer& renderer);
    
    TAILS_API ISlot* addWidget(std::shared_ptr<SWidget> content);
    
    template<typename T>
    ISlot* addWidget()
    {
        return addWidget(std::make_shared<T>());
    }
}

#endif // TAILS_WIDGET_SUBSYSTEM_HPP
