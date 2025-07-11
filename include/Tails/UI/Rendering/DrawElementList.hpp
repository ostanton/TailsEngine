#ifndef TAILS_UI_DRAW_ELEMENT_LIST_HPP
#define TAILS_UI_DRAW_ELEMENT_LIST_HPP

#include <Tails/Core.hpp>
#include <Tails/Templated/SharedRef.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Colour.hpp>

#include <vector>

namespace tails
{
    class CTexture;
}

namespace tails::ui
{
    struct SLayoutData;

    class TAILS_API CDrawElementList
    {
    public:
        struct SElement
        {
            SVector2f position;
            SVector2f size;
            SColour colour;
            std::shared_ptr<CTexture> texture;
        };

        using ElementVector = std::vector<SElement>;
        using Iterator = ElementVector::iterator;
        using ConstIterator = ElementVector::const_iterator;

        void add(
            const SLayoutData& layoutData,
            const TSharedRef<CTexture>& texture,
            SColour colour
        );

        void add(const SLayoutData& layoutData, SColour colour);

        [[nodiscard]] Iterator begin();
        [[nodiscard]] Iterator end();
        [[nodiscard]] ConstIterator begin() const;
        [[nodiscard]] ConstIterator end() const;

    private:
        std::vector<SElement> m_elements;
    };
}

#endif // TAILS_UI_DRAW_ELEMENT_LIST_HPP
