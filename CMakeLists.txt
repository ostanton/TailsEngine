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

# These definitions are subject to change, the engine is very young still

# Compiler definitions (I only use MSVC or GCC, so other compilers won't be well supported)
# See https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
# Microsoft Visual C
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(TailsEngine PUBLIC TAILS_MSVC)
# GNU Compiler Collection (GCC, etc.)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(TailsEngine PUBLIC TAILS_GNU)
# Clang (does not include AppleClang)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(TailsEngine PUBLIC TAILS_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_definitions(TailsEngine PUBLIC TAILS_APPLECLANG)
endif ()

# Platform definitions
# See https://stackoverflow.com/questions/9160335/os-specific-instructions-in-cmake-how-to
# and https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(TailsEngine PUBLIC TAILS_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(TailsEngine PUBLIC TAILS_APPLE)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(TailsEngine PUBLIC TAILS_LINUX)
endif ()

# Might want mINI to be public too? Would the user want it?
target_include_directories(
    TailsEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${mINI_SOURCE_DIR}/src
)

target_link_libraries(
    TailsEngine
    PUBLIC
        sfml-graphics
        sfml-audio
        nlohmann_json::nlohmann_json
)

target_compile_features(TailsEngine PUBLIC cxx_std_20)
