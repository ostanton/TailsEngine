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
#include <string>

namespace tails
{
    class CClassRegistry;
    struct SEngineSettings;

    struct TAILS_API SWindowProperties final
    {
        std::string title {"Tails Engine"};
        sf::Vector2u resolution {1280, 720};

        [[nodiscard]] std::string toString() const;
    };

    struct TAILS_API SRenderProperties final
    {
        sf::Vector2u resolution {240, 160};

        [[nodiscard]] std::string toString() const;
    };
    
    class TAILS_API CEngine final : public CObject, public ITickable, public sf::Drawable
    {
    public:
        CEngine();
        explicit CEngine(std::unique_ptr<SEngineSettings> engineSettings);
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
        [[nodiscard]] SEngineSettings& getSettings() const {return *m_settings;}

    protected:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
    private:
        void initMembers();
        void initInternalRender();
        void initWorldLevel(std::string path);
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

        /**
         * Whether the engine is currently running. This should probably always be true
         * (unless the game is closing)!
         */
        bool m_running {true};

        /**
         * The world associated with the engine.
         */
        CWorld m_world;

        SRenderProperties m_renderProperties;
        SWindowProperties m_windowProperties;
        std::unique_ptr<SEngineSettings> m_settings;

        float m_lifeTime {0.f};
    };
}

#endif // TAILS_ENGINE_HPP
