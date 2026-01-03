# CMakeLists.txt for Fundamentals Intermediate

# Intermediate level examples
add_executable(pointers pointers.c)
add_executable(structures structures.c)
add_executable(preprocessor preprocessor.c)

# Header example (multi-file program)
add_executable(header_example 
    header_example.c 
    math_utils.c
)

# Set output directory
set_target_properties(pointers structures preprocessor header_example
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fundamentals/intermediate/$<CONFIG>"
)

# Link math library on Unix-like systems only
if(UNIX)
    target_link_libraries(header_example m)
endif()
