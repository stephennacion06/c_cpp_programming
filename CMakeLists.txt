cmake_minimum_required(VERSION 3.15)

project(CPP_Knowledge_Repository 
    VERSION 1.0.0
    DESCRIPTION "C/C++ Knowledge Repository with Examples"
    LANGUAGES C CXX
)

# Set C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler-specific settings
if(MSVC)
    # MSVC-specific settings
    add_compile_options(/W4)  # Warning level 4
    add_compile_options(/permissive-)  # Conformance mode
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Zi)  # Debug information
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC and Clang settings
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g)  # Debug information
        add_compile_options(-O0)  # No optimization
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O3)  # Full optimization
    endif()
endif()

# Enable testing
enable_testing()

# Print build configuration
message(STATUS "")
message(STATUS "=== C/C++ Knowledge Repository Build Configuration ===")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID} ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "C Standard: ${CMAKE_C_STANDARD}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Output Directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "=====================================================")
message(STATUS "")

# Add subdirectories (uncomment as you add examples)
add_subdirectory(fundamentals/beginner)
add_subdirectory(data-structures/beginner)
# add_subdirectory(fundamentals/intermediate)
# add_subdirectory(fundamentals/advanced)
# add_subdirectory(data-structures/intermediate)
# add_subdirectory(algorithms)
# add_subdirectory(memory-management)
# add_subdirectory(best-practices)
# add_subdirectory(projects)

# Install targets (optional)
# install(TARGETS your_target
#     RUNTIME DESTINATION bin
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
# )
