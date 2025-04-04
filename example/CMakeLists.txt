project(Tails)

add_executable(
    TailsEXE
        main.cpp
        Player.hpp
        Player.cpp
        Bullet.hpp
)
target_link_libraries(
    TailsEXE
    PRIVATE 
        Tails
)

if (PSP)
    create_pbp_file(
        TARGET TailsEXE
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE "Tails"
        VERSION 01.00
    )
endif ()

set_target_properties(
    TailsEXE
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)
