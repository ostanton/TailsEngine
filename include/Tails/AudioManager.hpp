#ifndef TAILS_AUDIO_MANAGER_HPP
#define TAILS_AUDIO_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace tails
{
    class IBus;
    
    class TAILS_API CAudioManager final
    {
    public:
        template<Derives<IBus> T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        static IBus* createBus(std::string_view busName, ArgsT&&... args)
        {
            return addBus(busName, std::make_unique<T>(std::forward<ArgsT>(args)...));
        }

        [[nodiscard]] static IBus* getBus(std::string_view busName);

        [[nodiscard]] static bool busExists(std::string_view busName);
        
    private:
        CAudioManager() = default;
        
        static IBus* addBus(std::string_view busName, std::unique_ptr<IBus> bus);
        static CAudioManager& get();

        std::unordered_map<size_t, std::unique_ptr<IBus>> m_buses;
    };
}

#endif // TAILS_AUDIO_MANAGER_HPP
