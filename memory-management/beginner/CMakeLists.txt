# Memory Management - Beginner Level Examples

# stack_vs_heap - demonstrates performance and behavior differences
add_executable(stack_vs_heap stack_vs_heap.c)
set_target_properties(stack_vs_heap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/memory-management/beginner"
)

message(STATUS "Added Memory Management Beginner examples")
