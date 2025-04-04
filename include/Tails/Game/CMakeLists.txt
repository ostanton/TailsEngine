project(Tails)

target_sources(
    Tails
    PRIVATE
        Level.hpp
        Actor.hpp
)

add_subdirectory(Components)
