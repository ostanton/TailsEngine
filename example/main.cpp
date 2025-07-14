#include "MyWidget.hpp"

#include <Tails/Application.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/String.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/UI/Layout/StackBox.hpp>
#include <Tails/UI/Layout/Canvas.hpp>
#include <Tails/Memory.hpp>
#include <Tails/Log.hpp>
#include <Tails/Input/Event.hpp>
#include <Tails/Templated/Array.hpp>
#include <Tails/Audio/AudioSubsystem.hpp>
#include <Tails/Audio/BusHandle.hpp>
#include <Tails/Assets/Sound.hpp>
#include <Tails/Assets/AssetPtr.hpp>

#include "Tails/Debug.hpp"
#include "Tails/Input/InputSubsystem.hpp"
#include "Tails/Renderer/Renderer.hpp"

class CTestActor : public tails::CActor
{
public:
    CTestActor()
    {
        auto const sprite = createComponent<tails::CSpriteComponent>();
        sprite->size = {32.f, 32.f};
        sprite->colour = tails::SColour::magenta;
        setRootComponent(sprite);
    }
};

TAILS_REGISTER_ACTOR(CTestActor, "TestActor")

class CTestActor2 : public tails::CActor
{
public:
    CTestActor2()
    {
        auto const sprite = createComponent<tails::CSpriteComponent>();
        sprite->size = {32.f, 32.f};
        sprite->colour = tails::SColour::cyan;
        setRootComponent(sprite);
    }
};

TAILS_REGISTER_ACTOR(CTestActor2, "TestActor2")

struct STestStruct
{
    STestStruct(const int j)
        : i(j)
    {}
    
    int i {0};
};

namespace
{
    std::shared_ptr<CMyWidget> gMyWidget;

    void pollInputCallback(const tails::CEvent& ev)
    {
        if (auto const keyEv = ev.getIf<tails::CEvent::SKeyDown>())
        {
            if (keyEv->key == tails::EKeys::Escape)
                tails::app::exit();
        }
    }
}

int main(const int argc, char* argv[])
{
    using namespace tails;

    // app initialisation
    constexpr SWindowInfo windowInfo {
        .title = "My game!",
    };
    if (!app::init(argc, argv, windowInfo))
        return -1;

    // world and levels
    {
        auto const level = world::getCurrentLevel();
        if (!level)
            return 0;

        auto const player = level->spawnActor(
            "Player",
            {
                {0.f},
                0.f,
                {1.f, 1.f}
            }
        );
        level->spawnActor("TestActor", STransform2D::identity());
    }

    // widgets
    {
        gMyWidget = ui::createWidget<CMyWidget>(ui::getRootPanel());
        const std::vector colours {SColour::magenta, SColour::blue, SColour::green, SColour::red};
        gMyWidget->refreshContents(colours);
        auto const myWidgetSlot = ui::CCanvas::slotAsCanvasSlot(gMyWidget);
        myWidgetSlot->position.x = 16.f;
        myWidgetSlot->position.y = 16.f;
    }

    // memory functions
    {
        auto const testStruct = mem::alloc<STestStruct>();
        TAILS_LOG_VA(Game, Message, "Test Struct value: {}", testStruct->i);
        mem::construct(*testStruct, 7);
        TAILS_LOG_VA(Game, Message, "Test Struct value: {}", testStruct->i);
        mem::destroy(testStruct);
    }

    // dynamic array
    {
        TArray<STestStruct> testStructs;
        testStructs.add(STestStruct {55});
        testStructs.emplace(76);
        for (usize i {0}; i < testStructs.size(); i++)
        {
            TAILS_LOG(Game, Message, TAILS_FMT("TestStruct {} value: {}", i, testStructs[i].i));
        }
    }

    // sounds
    {
        // doesn't play the sound (yet), just testing that it fails gracefully
        TAssetPtr<CSound> mySound {"test_sound.wav"};
        auto testBusHandle = audio::addBus("test_bus");
        testBusHandle.playSound(mySound.load());
    }

    // clang things i is unused! So commenting out for now
    //TStaticArray<int, 5> numbers {4, 2, 6, 4, 8};
    //for (const auto i : numbers)
    //{
    //    TAILS_LOG(Game, Message, TAILS_FMT("Number is: {}", i));
    //}

    // default run sequence
    //app::run();

    auto matrixToString = [](const SMatrix3f& matrix) -> CString
    {
        return std::format(
            "[ {} , {} , {} ]\n[ {} , {} , {} ]\n[ {} , {} , {} ]",
            matrix.matrix[0][0], matrix.matrix[0][1], matrix.matrix[0][2],
            matrix.matrix[1][0], matrix.matrix[1][1], matrix.matrix[1][2],
            matrix.matrix[2][0], matrix.matrix[2][1], matrix.matrix[2][2]
        );
    };

    auto level = world::getCurrentLevel();
    auto testActor = level->spawnActor<CTestActor2>(
        {{}, 0.f, {2.f}},
        6
    );
    // customised run sequence with custom input polling callback (to close the window with the escape key)
    while (!app::shouldExit())
    {
        app::startFrame();
        app::pollInput(pollInputCallback);
        app::tick(app::getCurrentFrameInfo().getDeltaSeconds());
        auto mousePos = level->screenToWorld(input::getMousePosition());
        testActor->setPosition(mousePos);
        app::render();
        app::endFrame();
    }

    app::deinit();
    return 0;
}
