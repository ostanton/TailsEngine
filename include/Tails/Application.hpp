#ifndef TAILS_APPLICATION_HPP
#define TAILS_APPLICATION_HPP

#include <Tails/Core.hpp>
#include <Tails/Window.hpp>
#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    class CString;
    class IApplication;
    class IEventPoller;
    class IRenderer;
    class CEvent;
    struct SEntryPoint;

    /**
     * Structure for general application creation data. Used as a global variable so different
     * platforms can use it no matter how they perform their own setups
     */
    struct TAILS_API SAppCreateData
    {
        const char* name;
    };

    extern SAppCreateData gAppCreateData;

    /**
     * Platform-agnostic application. Creates the necessary things like a window, etc. for the specific
     * platform, and polls events, renders, etc. for it. E.g.:
     * - If on Windows, create a window, poll window events, render to window, etc.
     * - If on PSP, setup PSP module info, create window, poll, etc.
     */
    class TAILS_API IApplication
    {
        friend SEntryPoint;
        
    public:
        IApplication() = delete;
        explicit IApplication(SVector2u windowSize);
        IApplication(const IApplication&) = default;
        IApplication(IApplication&&) noexcept = default;
        IApplication& operator=(const IApplication&) = default;
        IApplication& operator=(IApplication&&) noexcept = default;
        virtual ~IApplication() = default;

        [[nodiscard]] static IApplication& get();

        [[nodiscard]] float getDeltaSeconds() const noexcept;
        [[nodiscard]] float getFPS() const noexcept;
        [[nodiscard]] float getAverageFPS() const noexcept;

        [[nodiscard]] CAssetManager& getAssetManager() noexcept;
        [[nodiscard]] const CAssetManager& getAssetManager() const noexcept;

        virtual void exit();

    protected:
        // TODO - could abstract args to a more user-friendly struct
        virtual bool init(int argc, char* argv[]);
        virtual bool run();
        virtual void shutdown();

        void pollInput();

        /**
         * Where you specify how this application handles various hard-coded actions (like closing, etc.)
         * @param ev Last polled event
         */
        virtual void onInputEvent(const CEvent& ev) = 0;
        virtual void tick(float deltaSeconds);
        void render();
        virtual void cleanup();

        [[nodiscard]] virtual bool shouldExit() const;

    private:
        static void setInstance(IApplication& instance);

        CWindow m_window;
        CAssetManager m_assetManager;
        float m_currentDeltaSeconds {0.f};
        float m_averageFPS {0.f};
    };
}

#endif // TAILS_APPLICATION_HPP
