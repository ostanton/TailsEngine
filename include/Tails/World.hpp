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
        CWorld(const CWorld&) = delete;
        CWorld(CWorld&&) noexcept = default;
        CWorld& operator=(const CWorld&) = delete;
        CWorld& operator=(CWorld&&) noexcept = default;
        ~CWorld() override;
        
        CLevel& openLevel(std::string path, std::unique_ptr<SLevelSettings> settings = nullptr);
        bool closeLevel(CLevel* level);
        bool closeLevel(size_t index);

        [[nodiscard]] CEngine& getEngine() const;
        [[nodiscard]] CLevel* getLevel(size_t index);
        [[nodiscard]] const CLevel* getLevel(size_t index) const;
        
    private:
        CWorld() = default;
        
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        std::vector<CLevel> m_openLevels;
    };
}

#endif // TAILS_WORLD_HPP
