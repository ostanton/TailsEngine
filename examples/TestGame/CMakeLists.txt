project(TailsEngine)

add_subdirectory(include)
add_subdirectory(src)

target_include_directories(TestGame PRIVATE include)