# CMakeLists.txt for Intermediate Exercises

# Intermediate exercises
add_executable(ex01_dynamic_array ex01_dynamic_array.c)
add_executable(ex02_linked_list ex02_linked_list.c)
add_executable(ex03_file_copy ex03_file_copy.c)

# Set output directory
set_target_properties(
    ex01_dynamic_array
    ex02_linked_list
    ex03_file_copy
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/exercises/intermediate/$<CONFIG>"
)
