cmake_minimum_required(VERSION 3.15)
project(RocketLeagueTASMod)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/backends
    ${CMAKE_SOURCE_DIR}/external/minhook/include
)

# ImGui source files
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
file(GLOB IMGUI_SOURCES 
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

# Project source files
file(GLOB_RECURSE SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Create DLL
add_library(RLTASMod SHARED
    ${SOURCES}
    ${IMGUI_SOURCES}
)

# Link libraries
target_link_libraries(RLTASMod
    d3d11.lib
    dxgi.lib
    ${CMAKE_SOURCE_DIR}/external/minhook/lib/libMinHook.x64.lib
)

# Set DLL properties
set_target_properties(RLTASMod PROPERTIES
    OUTPUT_NAME "RLTASMod"
    SUFFIX ".dll"
)

# Copy DLL to bin directory
add_custom_command(TARGET RLTASMod POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy 
    $<TARGET_FILE:RLTASMod>
    ${CMAKE_BINARY_DIR}/bin/RLTASMod.dll
)

# Add injector subdirectory
add_subdirectory(injector)
