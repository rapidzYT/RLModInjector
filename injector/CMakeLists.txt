cmake_minimum_required(VERSION 3.15)
project(RLTASInjector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(RLTASInjector Injector.cpp)

# Set output directory
set_target_properties(RLTASInjector PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
