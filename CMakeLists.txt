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

# Don't need to check if these are downloaded, CPM seems to do it for us
# Could check on the user's PC elsewhere, but having a clean clone is good I think

# Build SFML statically
set(BUILD_SHARED_LIBS OFF)
set(SFML_USE_STATIC_STD_LIBS ON)

# Add SFML
CPMAddPackage("gh:SFML/SFML#2.6.1")

# Add nlohmann/json
CPMAddPackage("gh:nlohmann/json@3.11.3")

target_link_libraries(
    TailsEngine
    PUBLIC
        sfml-graphics
        sfml-audio
        nlohmann_json::nlohmann_json
)

target_include_directories(
    TailsEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(TailsEngine PUBLIC cxx_std_20)
