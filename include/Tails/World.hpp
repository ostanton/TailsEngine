#ifndef TAILS_WORLD_HPP
#define TAILS_WORLD_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <string>
#include <memory>
#include <vector>

namespace tails
{
    class CEngine;
    class CLevel;
    struct SLevelSettings;
    
    class TAILS_API CWorld final : public CObject, public ITickable, public sf::Drawable
    {
        friend CEngine;

    public:
        CLevel* openLevel(std::string path, std::unique_ptr<SLevelSettings> settings = nullptr);
        bool closeLevel(CLevel* level);
        bool closeLevel(size_t index);

        [[nodiscard]] CEngine& getEngine() const;
        [[nodiscard]] CLevel* getLevel(size_t index) const;
        
    private:
        CWorld() = default;
        
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        // could make automatically allocated? Would including level header here be very bad??
        std::vector<std::unique_ptr<CLevel>> m_openLevels;
    };
}

#endif // TAILS_WORLD_HPP
