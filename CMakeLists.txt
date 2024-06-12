cmake_minimum_required(VERSION 3.25.1)

project(TailsEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(BUILD_EXAMPLES "Build the included examples" ON)

add_subdirectory(include)
add_subdirectory(src)

# dunno how to specify specific directories for each example,
# so unfortunately they'll all be dumped in the same build/bin!
if (BUILD_EXAMPLES)
    message(STATUS "Building examples...")
    add_subdirectory(examples)
    message(STATUS "Examples built!? Is this where they finish building?? Huh?")
endif(BUILD_EXAMPLES)

include(FetchContent)

message(STATUS "Fetching SFML...")
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
message(STATUS "Declared SFML!")
message(STATUS "Making SFML available...")
FetchContent_MakeAvailable(SFML)
message(STATUS "Fetched SFML!")

message(STATUS "Fetching nlohmann/json...")
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
message(STATUS "Declared nlohmann/json!")
message(STATUS "Making nlohmann/json available...")
FetchContent_MakeAvailable(json)
message(STATUS "Fetched nlohmann/json!")

target_include_directories(
    TailsEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(
    TailsEngine
    PUBLIC
        sfml-graphics
        sfml-audio
        nlohmann_json::nlohmann_json
)
target_compile_features(TailsEngine PRIVATE cxx_std_20)
