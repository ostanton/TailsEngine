project(TailsGame)

add_executable(
    TestGame
    main.cpp
    MyEngine.cpp
    MyState.cpp
    MyEntityRegistry.cpp
    MyEntity.cpp
    MyRegistrySubsystem.cpp
    MyScreen.cpp
)

target_link_libraries(
    TestGame
    PRIVATE
        TailsEngine
)
