cmake_minimum_required(VERSION 3.25.1)

project(TailsEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(include)
add_subdirectory(src)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_include_directories(
    TailsEngine
    PUBLIC
        include
)
target_link_libraries(
    TailsEngine
    PUBLIC
        sfml-graphics
        sfml-audio
        nlohmann_json::nlohmann_json
)
target_compile_features(TailsEngine PRIVATE cxx_std_20)
