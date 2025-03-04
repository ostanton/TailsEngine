cmake_minimum_required(VERSION 3.24)

project(TailsEngine LANGUAGES CXX)

set(TAILS_BUILD_SHARED OFF CACHE BOOL "Whether to build shared/dynamically (default - OFF)")
set(TAILS_BACKEND "SFML3" CACHE STRING "Backend for Tails Engine to use (default - 'SFML3')")

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

if (TAILS_BUILD_SHARED)
    message("-- TailsEngine: Building shared library")
    add_library(TailsEngine SHARED)
else ()
    message("-- TailsEngine: Building static library")
    add_library(TailsEngine STATIC)
endif ()

add_subdirectory(src/Tails)
add_subdirectory(include/Tails)

# Don't need to check if these are downloaded, CPM seems to do it for us
# Could check on the user's PC elsewhere, but having a clean clone is good I think

message("-- TailsEngine: Using backend ${TAILS_BACKEND}")

if (TAILS_BACKEND STREQUAL "SFML3")
    add_subdirectory(include/Platform/SFML3)
    
    # Build SFML statically
    # TODO - should this be checked with TAILS_BUILD_SHARED or something else?
    set(BUILD_SHARED_LIBS OFF)
    set(SFML_USE_STATIC_STD_LIBS ON)
    
    # Add SFML
    CPMAddPackage("gh:SFML/SFML#3.0.0")
    target_compile_definitions(TailsEngine PUBLIC TAILS_BACKEND_SFML3)
    
    target_link_libraries(
        TailsEngine
        PUBLIC
            SFML::Graphics
            SFML::Audio
            SFML::Network
    )

# Windows/Darwin/Linux/etc.
elseif (TAILS_BACKEND STREQUAL "Native")
    add_subdirectory(include/Platform/${CMAKE_SYSTEM_NAME})
    
    target_compile_definitions(TailsEngine PUBLIC TAILS_BACKEND_NATIVE)
    
else ()
    message("-- TailsEngine: Invalid backend!")
endif ()

# Add nlohmann/json
CPMAddPackage("gh:nlohmann/json@3.11.3")

# Add LDtkLoader
CPMAddPackage("gh:Madour/LDtkLoader#1.5.3.1")
set_property(TARGET LDtkLoader PROPERTY
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_MSVC)
    
    if (NOT TAILS_BUILD_SHARED)
        # Use static RuntimeLibrary in MSVC instead of DLL
        set_property(TARGET TailsEngine PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_GNU)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(TailsEngine PUBLIC TAILS_COMP_CLANG)
else ()
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
        nlohmann_json::nlohmann_json
        LDtkLoader::LDtkLoader
)

target_include_directories(
    TailsEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(TailsEngine PUBLIC cxx_std_20)
