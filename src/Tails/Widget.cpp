#include <Tails/Widget.hpp>
#include <Tails/WidgetContainer.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    WContainer* CWidget::getParent() const
    {
        if (!outer) return nullptr;

        if (auto parent = dynamic_cast<WContainer*>(outer))
            return parent;

        return nullptr;
    }

    void CWidget::destroy()
    {
        markForDestroy();
    }

    CEngine& CWidget::getEngine() const
    {
        return *getTypedOuter<CEngine>();
    }
}
