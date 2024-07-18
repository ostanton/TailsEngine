cmake_minimum_required(VERSION 3.25.1 FATAL_ERROR)

project(TailsEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Download and include CPM.cmake
message("-- Tails: Downloading CPM.cmake")
file(
    DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.0/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
message("-- Tails: Successfully downloaded CPM.cmake")

# Where TailsEngine static library target is defined
add_subdirectory(src/Tails)
add_subdirectory(include/Tails)

# DEPENDENCIES
message("-- Tails: Adding package dependencies")
# SFML
# Build SFML statically
set(SFML_USE_STATIC_STD_LIBS ON)
set(BUILD_SHARED_LIBS OFF)
CPMAddPackage("gh:SFML/SFML#2.6.1")

# nlohmann/json
CPMAddPackage("gh:nlohmann/json@3.11.3")

# metayeti/mINI
CPMAddPackage("gh:metayeti/mINI#0.9.15")

message("-- Tails: Finished adding packages")

target_include_directories(
    TailsEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${mINI_SOURCE_DIR}/src
)

target_link_libraries(
    TailsEngine
    PRIVATE
        sfml-graphics
        sfml-audio
        nlohmann_json::nlohmann_json
)

target_compile_features(TailsEngine PRIVATE cxx_std_20)
