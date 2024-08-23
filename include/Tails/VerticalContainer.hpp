#ifndef TAILS_VERTICALCONTAINER_HPP
#define TAILS_VERTICALCONTAINER_HPP

#include <Tails/Config.hpp>
#include <Tails/WidgetContainer.hpp>
#include <Tails/Padding.hpp>

namespace tails
{
    class TAILS_API WVerticalContainer : public WContainer
    {
    public:
        void setChildPadding(const SPadding& padding);
        [[nodiscard]] SPadding& getChildPadding() {return m_childPadding;}
        [[nodiscard]] const SPadding& getChildPadding() const {return m_childPadding;}

    private:
        void drawChild(size_t childIndex) const override;

        std::unique_ptr<ISerialisable> clone() const override;

        SPadding m_childPadding;
    };
}

#endif // TAILS_VERTICALCONTAINER_HPP
