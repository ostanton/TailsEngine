#ifndef TAILS_BUS_HANDLE_HPP
#define TAILS_BUS_HANDLE_HPP

#include <Tails/Core.hpp>
#include <Tails/Templated/Optional.hpp>

#include <memory>

namespace tails
{
    class CSound;
    class CString;
}

namespace tails::audio
{
    /**
     * Essentially a mediator between the user and the bus itself, hiding how buses are stored and accessed
     */
    struct TAILS_API SBusHandle final
    {
        TOptional<usize> index {};

        void pause();
        void stop();
        void setVolume(float volume);
        void setName(CString name);

        void playSound(std::shared_ptr<CSound> sound);

        [[nodiscard]] bool isPlaying() const noexcept;
        [[nodiscard]] float getVolume() const noexcept;
        [[nodiscard]] CString getName() const noexcept;
    };
}

#endif // TAILS_BUS_HANDLE_HPP
