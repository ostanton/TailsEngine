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

    nlohmann::json CWidget::serialise() const
    {
        // TODO - serial stuff
        nlohmann::json obj;
        return obj;
    }

    void CWidget::deserialise(const nlohmann::json& obj)
    {
        // TODO - deserial things
    }
}
