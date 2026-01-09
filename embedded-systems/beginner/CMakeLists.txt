# Embedded Systems - Beginner Level Examples

# volatile_keyword - demonstrates why volatile is critical for hardware
add_executable(volatile_keyword volatile_keyword.c)
set_target_properties(volatile_keyword PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/embedded-systems/beginner"
)

# bit_manipulation - essential bit operations for embedded
add_executable(bit_manipulation bit_manipulation.c)
set_target_properties(bit_manipulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/embedded-systems/beginner"
)

# memory_mapped_io - demonstrates MMIO for hardware control
add_executable(memory_mapped_io memory_mapped_io.c)
set_target_properties(memory_mapped_io PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/embedded-systems/beginner"
)

message(STATUS "Added Embedded Systems Beginner examples")
