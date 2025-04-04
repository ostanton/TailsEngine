project(Tails)

target_sources(
    Tails
    PRIVATE
        Level.cpp
        Actor.cpp
)

add_subdirectory(Components)
