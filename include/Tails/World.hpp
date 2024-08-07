#ifndef TAILS_WORLD_HPP
#define TAILS_WORLD_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <string>
#include <memory>

namespace tails
{
    class CEngine;
    class CLevel;
    
    class TAILS_API CWorld final : public CObject, public ITickable, public sf::Drawable
    {
        friend CEngine;

    public:
        void openLevel(std::string path);

        [[nodiscard]] CEngine& getEngine() const;
        [[nodiscard]] CLevel& getLevel() const {return *m_currentLevel;}
        
    private:
        CWorld() = default;
        
        void setDefaultLevel(std::string path);
        
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        std::unique_ptr<CLevel> m_currentLevel;
        std::unique_ptr<CLevel> m_levelToLoad;
    };
}

#endif // TAILS_WORLD_HPP
