cmake_minimum_required(VERSION 3.29.3 FATAL_ERROR)

project(TailsEngine LANGUAGES CXX)

# Download and include CPM
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.1/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

add_subdirectory(src/Tails)
add_subdirectory(include/Tails)

# Build SFML statically
set(BUILD_SHARED_LIBS OFF)
set(SFML_USE_STATIC_STD_LIBS ON)

# Add SFML
CPMAddPackage("gh:SFML/SFML#2.6.1")

target_link_libraries(TailsEngine PUBLIC sfml-graphics)
target_include_directories(TailsEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(TailsEngine PUBLIC cxx_std_20)
