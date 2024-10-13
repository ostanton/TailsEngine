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
        template<DerivesBus T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        static IBus* createBus(const std::string& busName, ArgsT&&... args)
        {
            return addBus(busName, std::make_unique<T>(std::forward<ArgsT>(args)...));
        }

        [[nodiscard]] static IBus* getBus(std::string_view busName);

        [[nodiscard]] static bool busExists(size_t bus);
        
    private:
        static IBus* addBus(const std::string& busName, std::unique_ptr<IBus> bus);
        static CAudioManager& get();

        std::unordered_map<std::string, std::unique_ptr<IBus>> m_buses;
    };
}

#endif // TAILS_AUDIO_MANAGER_HPP
