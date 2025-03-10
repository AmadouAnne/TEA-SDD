# Minimum CMake version required
cmake_minimum_required(VERSION 3.0)

# Project name and version
project(BiColorTree VERSION 1.0)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include the header files directory
include_directories(${CMAKE_SOURCE_DIR})

# Define the main library
add_library(bicolor_tree bicolor-tree.c)

# Test executable for insertion testing
add_executable(gen-data-rb gen-data-rb.c)
target_link_libraries(gen-data-rb bicolor_tree)

# Test executable for menu operations
add_executable(test_menu_bitree test-menu-simple.c)
target_link_libraries(test_menu_bitree bicolor_tree)

# Optional: Enable compiler warnings for better code quality
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(bicolor_tree PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_insert_bicolor PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_menu_bitree PRIVATE -Wall -Wextra -pedantic)
endif()
