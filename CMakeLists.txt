cmake_minimum_required(VERSION 3.28.3)

project(TailsEngine LANGUAGES CXX)

# Download CPM if it does not already exist
if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")
    message("-- TailsEngine: CPM is already downloaded")
else ()
    message("-- TailsEngine: Downloading CPM")
    file(
      DOWNLOAD
      https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.1/CPM.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    )
endif ()

# Include CPM
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

add_subdirectory(src/Tails)
add_subdirectory(include/Tails)

# Use static RuntimeLibrary in MSVC instead of DLL
set_property(TARGET TailsEngine PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Don't need to check if these are downloaded, CPM seems to do it for us
# Could check on the user's PC elsewhere, but having a clean clone is good I think

# Build SFML statically
set(BUILD_SHARED_LIBS OFF)
set(SFML_USE_STATIC_STD_LIBS ON)

# Add SFML
CPMAddPackage("gh:SFML/SFML#master")

# Add nlohmann/json
CPMAddPackage("gh:nlohmann/json@3.11.3")

# Add LDtkLoader
CPMAddPackage("gh:Madour/LDtkLoader#1.5.3.1")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_MSVC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_GNU)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_CLANG)
else()
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_UNKNOWN)
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(TailsEngine PUBLIC TAILS_OS_WIN32)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(TailsEngine PUBLIC TAILS_OS_APPLE)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(TailsEngine PUBLIC TAILS_OS_LINUX)
else ()
    target_compile_definitions(TailsEngine PUBLIC TAILS_OS_UNKNOWN)
endif ()

target_link_libraries(
    TailsEngine
    PUBLIC
        SFML::Graphics
        SFML::Audio
        SFML::Network
        nlohmann_json::nlohmann_json
        LDtkLoader::LDtkLoader
)

target_include_directories(
    TailsEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(TailsEngine PUBLIC cxx_std_20)
