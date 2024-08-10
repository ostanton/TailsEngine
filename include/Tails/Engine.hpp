#ifndef TAILS_ENGINE_HPP
#define TAILS_ENGINE_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/World.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>

#include <memory>

namespace tails
{
    class TAILS_API CEngine final : public CObject, public ITickable, public sf::Drawable
    {
    public:
        /**
         * Sets up engine with "engine.json" as engine setup file
         */
        CEngine();
        explicit CEngine(const std::string& engineSetupFile);
        ~CEngine() override;
    
        template<typename T, typename... Args>
        void setRenderTarget(Args&&... args)
        {
            static_assert(std::is_base_of_v<sf::RenderTarget, T>,
                "Failed to set engine render target, type does not derive sf::RenderTarget.");
            
            m_renderTarget = std::make_unique<T>(std::forward<Args>(args)...);
        }

        void run();
        void kill();

        [[nodiscard]] sf::RenderTarget& getRenderTarget() const {return *m_renderTarget;}
        [[nodiscard]] const sf::RenderStates& getRenderState() const {return m_renderStates;}
        [[nodiscard]] sf::RenderTexture& getInternalRenderTexture() {return m_renderTextureInternal;}
        [[nodiscard]] const sf::RenderTexture& getInternalRenderTexture() const {return m_renderTextureInternal;}
        [[nodiscard]] sf::View& getRenderView() {return m_renderView;}
        [[nodiscard]] const sf::View& getRenderView() const {return m_renderView;}
        [[nodiscard]] CWorld& getWorld() {return m_world;}
        [[nodiscard]] const CWorld& getWorld() const {return m_world;}

    protected:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
    private:
        void calculateInternalAspectRatio(sf::Vector2u windowSize);
        
        /**
         * The final render output
         */
        std::unique_ptr<sf::RenderTarget> m_renderTarget;
        
        /**
         * The internal rendering
         */
        sf::RenderTexture m_renderTextureInternal;

        /**
         * Describes how the internal render will be displayed in the final render.
         * E.g. aspect ratio, size, centring, etc.
         */
        sf::View m_renderView;
        
        sf::RenderStates m_renderStates;
        bool m_running {true};
        CWorld m_world;

        sf::Vector2u m_renderResolution {240, 160};
    };
}

#endif // TAILS_ENGINE_HPP
