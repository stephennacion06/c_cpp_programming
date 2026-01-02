cmake_minimum_required(VERSION 3.15)

# Beginner data structures examples
add_executable(array_operations array_operations.c)
add_executable(sorting sorting.c)
add_executable(searching searching.c)

# Set output directory
set_target_properties(
    array_operations sorting searching
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/data-structures/beginner"
)
