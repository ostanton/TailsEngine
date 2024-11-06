#ifndef TAILS_ENGINE_HPP
#define TAILS_ENGINE_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/World.hpp>
#include <Tails/Maths.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <ranges>

namespace tails
{
    class CClassRegistry;
    struct SEngineSettings;
    class CSubsystem;

    namespace ui
    {
        class CUISubsystem;
    }

    struct TAILS_API SWindowProperties final
    {
        std::string title {"Tails Engine"};
        sf::Vector2u resolution {1280, 720};

        [[nodiscard]] std::string toString() const;
    };

    struct TAILS_API SRenderProperties final
    {
        sf::Vector2u resolution {240, 160};
        bool maintainAspectRatio {true};

        [[nodiscard]] std::string toString() const;
    };
    
    class TAILS_API CEngine final : public CObject, public ITickable, public sf::Drawable
    {
    public:
        CEngine();
        explicit CEngine(std::unique_ptr<SEngineSettings> engineSettings);
        CEngine(const CEngine&) = delete;
        CEngine(CEngine&&) noexcept;
        CEngine& operator=(const CEngine&) = delete;
        CEngine& operator=(CEngine&&) noexcept;
        ~CEngine() override;
    
        template<Derives<sf::RenderTarget> T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        void setRenderTarget(ArgsT&&... args)
        {
            m_renderTarget = std::make_unique<T>(std::forward<ArgsT>(args)...);
        }

        template<Derives<CSubsystem> T, typename... ArgsT>
        requires ConstructibleUserType<T, ArgsT...>
        void registerSubsystem(const std::string_view id, ArgsT&&... args)
        {
            const std::size_t hashed {hash(id)};
            if (m_subsystems.contains(hashed))
            {
                CDebug::print("  Subsystem ", id, " is already registered");
                return;
            }

            registerSubsystemImpl(hashed, std::make_unique<T>(std::forward<ArgsT>(args)...));
            CDebug::print("  Registered ", id, " subsystem");
        }

        [[nodiscard]] CSubsystem* getSubsystem(std::string_view id) const;

        template<Derives<CSubsystem> T>
        T* getSubsystemOfType() const
        {
            if (m_subsystems.empty()) return nullptr;

            for (auto& subsystem : std::ranges::views::values(m_subsystems))
            {
                if (auto castedSubsystem = dynamic_cast<T*>(subsystem.get()))
                    return castedSubsystem;
            }

            return nullptr;
        }

        void run();
        void kill();

        [[nodiscard]] sf::RenderTarget& getRenderTarget() const {return *m_renderTarget;}
        
        [[nodiscard]] const sf::RenderStates& getRenderState() const noexcept {return m_renderStates;}

        [[nodiscard]] sf::RenderTexture& getInternalRenderTexture() noexcept {return m_renderTextureInternal;}
        [[nodiscard]] const sf::RenderTexture& getInternalRenderTexture() const noexcept {return m_renderTextureInternal;}

        [[nodiscard]] sf::View& getRenderView() noexcept {return m_renderView;}
        [[nodiscard]] const sf::View& getRenderView() const noexcept {return m_renderView;}

        [[nodiscard]] CWorld& getWorld() noexcept {return m_world;}
        [[nodiscard]] const CWorld& getWorld() const noexcept {return m_world;}

        [[nodiscard]] ui::CUISubsystem& getUISubsystem() noexcept;
        [[nodiscard]] const ui::CUISubsystem& getUISubsystem() const noexcept;

        [[nodiscard]] SEngineSettings& getSettings() const {return *m_settings;}

        [[nodiscard]] SRenderProperties& getRenderProperties() noexcept {return m_renderProperties;}
        [[nodiscard]] const SRenderProperties& getRenderProperties() const noexcept {return m_renderProperties;}

        [[nodiscard]] SWindowProperties& getWindowProperties() noexcept {return m_windowProperties;}
        [[nodiscard]] const SWindowProperties& getWindowProperties() const noexcept {return m_windowProperties;}

        [[nodiscard]] float getCurrentLifeTime() const noexcept {return m_lifeTime;}

        void setRenderTargetClearColour(sf::Color colour);
        [[nodiscard]] sf::Color getRenderTargetClearColour() const noexcept {return m_renderTargetClearColour;}
        
        void setRenderTextureInternalClearColour(sf::Color colour);
        [[nodiscard]] sf::Color getRenderTextureInternalClearColour() const noexcept {return m_renderTextureInternalClearColour;}

    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;
        
        void registerSubsystemImpl(std::size_t id, std::unique_ptr<CSubsystem> subsystem);
        void setupDefaultSubsystems();
        void initSubsystems();
        
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

        std::unordered_map<std::size_t, std::unique_ptr<CSubsystem>> m_subsystems;

        SRenderProperties m_renderProperties;
        SWindowProperties m_windowProperties;
        std::unique_ptr<SEngineSettings> m_settings;

        float m_lifeTime {0.f};

        sf::Color m_renderTargetClearColour {0, 0, 0, 255};
        sf::Color m_renderTextureInternalClearColour {0, 0, 0, 255};
    };
}

#endif // TAILS_ENGINE_HPP
