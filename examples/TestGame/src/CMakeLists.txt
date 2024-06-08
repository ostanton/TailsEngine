project(TailsGame)

add_executable(
    TestGame
    main.cpp
)

target_link_libraries(
    TestGame
    PRIVATE
        TailsEngine
)
