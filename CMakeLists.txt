cmake_minimum_required(VERSION 3.24)

project(Tails LANGUAGES CXX)

# Tails options
set(TAILS_BUILD_SHARED OFF CACHE BOOL "Whether to build shared/dynamically (default - OFF)")
set(TAILS_BUILD_EXAMPLES ON CACHE BOOL "Whether to build the examples or not (default - ON)")
set(TAILS_ENABLE_ASSERTS ON CACHE BOOL "Enable/disable asserts. Always off in release builds (default - ON)")
set(TAILS_ENABLE_PROFILING ON CACHE BOOL "Enable/disable profiling macros, independent of debug/release (default - ON)")
set(TAILS_ENABLE_LOGGING ON CACHE BOOL "Enable/disable logging macros, independent of debug/release (default - ON)")
# TODO - not sure on this!!
set(TAILS_TARGET_PLATFORM "Native" CACHE STRING "Choose a target platform to compile for. Supported: Native, PSP (default - Native)")

message("--")
message("-- Tails configuration:")
message("--   Shared:    ${TAILS_BUILD_SHARED}")
message("--              (TAILS_BUILD_SHARED)")
message("--   Asserts:   ${TAILS_ENABLE_ASSERTS}")
message("--              (TAILS_ENABLE_ASSERTS)")
message("--   Profiling: ${TAILS_ENABLE_PROFILING}")
message("--              (TAILS_ENABLE_PROFILING)")
message("--   Logging:   ${TAILS_ENABLE_LOGGING}")
message("--              (TAILS_ENABLE_LOGGING)")
message("--")

if (TAILS_BUILD_SHARED)
    add_library(Tails SHARED)
    target_compile_definitions(Tails PUBLIC TAILS_BUILD_SHARED)
else ()
    add_library(Tails STATIC)
endif ()

add_library(ostanton::Tails ALIAS Tails)

set_target_properties(
    Tails
    PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
)

if (TAILS_ENABLE_ASSERTS)
    target_compile_definitions(Tails PUBLIC TAILS_ENABLE_ASSERTS)
endif ()

if (TAILS_ENABLE_PROFILING)
    target_compile_definitions(Tails PUBLIC TAILS_ENABLE_PROFILING)
endif ()

if (TAILS_ENABLE_LOGGING)
    target_compile_definitions(Tails PUBLIC TAILS_ENABLE_LOGGING)
endif ()

add_subdirectory(include/Tails)
add_subdirectory(src)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)

# external libraries
set(TAILS_LIBS)

# SDL3
message("--")
message("-- Tails: Fetching SDL3")
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.10
)
FetchContent_MakeAvailable(SDL3)
list(APPEND TAILS_LIBS SDL3::SDL3)

# SDL3_image
# TODO
#set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
#set(SDL3_DIR "${SDL3_BINARY_DIR}")
#message("-- Tails: SDL3_BINARY_DIR = ${SDL3_BINARY_DIR}")
#FetchContent_Declare(
#    SDL3_image
#    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
#    GIT_TAG release-3.2.4
#)
#FetchContent_MakeAvailable(SDL3_image)
#list(APPEND TAILS_LIBS SDL3_image::SDL3_image)

target_include_directories(
    Tails
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (TAILS_ENABLE_LOGGING)
    # some logging lib? spdlog doesn't seem to work!
endif ()

if (PSP)
    list(APPEND TAILS_LIBS pspdebug pspdisplay pspge)
endif ()

message("--")
message("-- Tails: Linking libraries '${TAILS_LIBS}'")
message("--")
target_link_libraries(Tails PUBLIC ${TAILS_LIBS})
target_compile_features(Tails PUBLIC cxx_std_20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Tails PRIVATE /W3 /WX)
endif ()

if (TAILS_BUILD_EXAMPLES)
    # Examples
    add_subdirectory(example)
endif ()
