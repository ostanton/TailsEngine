#ifndef TAILS_WINDOW_HPP
#define TAILS_WINDOW_HPP

#include <Tails/Core.hpp>
#include <Tails/Templated/Bitset.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Templated/Optional.hpp>

namespace tails
{
    class CEvent;

    enum class EWindowFlags : u8
    {
        Resizable = 1 << 0,
        Fullscreen = 1 << 1,
        Borderless = 1 << 2,
        Minimised = 1 << 3,
        Maximised = 1 << 4,
    };

    struct TAILS_API SWindowInfo
    {
        const char* title {"Tails Engine"};
        SVector2u size {1280, 720};
        SVector2u minSize {640, 360};
        TBitset<EWindowFlags> flags {EWindowFlags::Resizable};
    };

    namespace window
    {
        TAILS_API bool init(const SWindowInfo& windowInfo);
        TAILS_API void deinit();
        TAILS_API TOptional<CEvent> pollInput();

        TAILS_API const char* getTitle() noexcept;
        TAILS_API SVector2i getPosition() noexcept;

        /**
         * Gets the window's size, or {0, 0} if it fails in any way
         * @return Window size
         */
        TAILS_API SVector2u getSize() noexcept;
    }
}

#endif // TAILS_WINDOW_HPP
