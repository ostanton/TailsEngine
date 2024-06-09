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
endif(BUILD_EXAMPLES)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
    simpleson
    GIT_REPOSITORY https://github.com/gregjesl/simpleson
    GIT_TAG master
)
FetchContent_MakeAvailable(simpleson)

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
        simpleson
)
target_compile_features(TailsEngine PRIVATE cxx_std_20)
