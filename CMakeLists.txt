# Project Info
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
cmake_policy(VERSION 3.9)
project(CrossWindow)
enable_language(C)
enable_language(CXX)

# CMake Settings
set(CMAKE_SUPPRESS_REGENERATION true)
set(DCMAKE_GENERATOR_PLATFORM "x64")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_AUTOMOC ON)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeHelpers")
#include(generate_win32_files)
#include(generate_macos_files)

# =============================================================

# Options
set(OPERATING_SYSTEM AUTO CACHE STRING "Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM") 
set_property(CACHE OPERATING_SYSTEM PROPERTY STRINGS AUTO VULKAN OPENGL DIRECTX METAL NOOP)

if(OPERATING_SYSTEM STREQUAL "AUTO")
    if (WIN32)
    set(OPERATING_SYSTEM "WINDOWS" CACHE STRING "Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM" FORCE)
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPERATING_SYSTEM "MACOS" CACHE STRING "Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM" FORCE)
    elseif (UNIX)
    set(OPERATING_SYSTEM "LINUX" CACHE STRING "Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM" FORCE)
    endif()
endif()

set(OPERATING_SYSTEM_PATH "Noop")

if(OPERATING_SYSTEM STREQUAL "WINDOWS")
    set(OPERATING_SYSTEM_PATH "Windows")
elseif(OPERATING_SYSTEM STREQUAL "MACOS")
    set(OPERATING_SYSTEM_PATH "MacOS")
elseif(OPERATING_SYSTEM STREQUAL "LINUX")
    set(OPERATING_SYSTEM_PATH "Linux")
elseif(OPERATING_SYSTEM STREQUAL "ANDROID")
    set(OPERATING_SYSTEM_PATH "Android")
elseif(OPERATING_SYSTEM STREQUAL "IOS")
    set(OPERATING_SYSTEM_PATH "iOS")
elseif(OPERATING_SYSTEM STREQUAL "WASM")
    set(OPERATING_SYSTEM_PATH "WASM")
elseif(OPERATING_SYSTEM STREQUAL "NOOP")
    set(OPERATING_SYSTEM_PATH "Noop")
endif()

MESSAGE( STATUS "Building CrossWindow for " ${OPERATING_SYSTEM_PATH} )

# =============================================================

# Sources

file(GLOB_RECURSE FILE_SOURCES RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/CrossWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/CrossWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Common/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Common/*.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Common/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/${OPERATING_SYSTEM_PATH}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/${OPERATING_SYSTEM_PATH}/*.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/${OPERATING_SYSTEM_PATH}/*.h
)

# Solution Filters
foreach(source IN LISTS FILE_SOURCES)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    string(REPLACE "src" "" source_path_final "${source_path_msvc}")
    source_group("${source_path_final}" FILES "${source}")
endforeach()

# Main files
file(GLOB_RECURSE MAIN_SOURCES RELATIVE
    ${CMAKE_HOME_DIRECTORY}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Main/${OPERATING_SYSTEM_PATH}Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Main/${OPERATING_SYSTEM_PATH}Main.mm
)


set(XMAIN_SOURCES ${MAIN_SOURCES} PARENT_SCOPE)

# =============================================================

# CrossWindow Functions
function(xwin_setup versionMajor versionMinor versionPatch versionRevision companyName iconPath)
    # @TODO - implement
    message("Warning: xwin_setup has not yet been implemented.")
endfunction()

function(xwin_add_executable targetProject targetSources)
    message("Creating CrossWindow executable:")

    foreach(source IN LISTS XMAIN_SOURCES)
        source_group("" FILES "${source}")
    endforeach()

    set(XWIN_FILES ${XMAIN_SOURCES} ${targetSources})

    if(OPERATING_SYSTEM STREQUAL "WINDOWS")
        add_executable(
            ${targetProject}
            WIN32
            ${XWIN_FILES}
        )
    elseif(OPERATING_SYSTEM STREQUAL "MACOS")
        add_executable(
            ${targetProject}
            MACOSX_BUNDLE

        )
    elseif(OPERATING_SYSTEM STREQUAL "IOS")
        add_executable(
            ${targetProject}
            ${MAIN_SOURCES}
            ${targetSources}
        )
    elseif(OPERATING_SYSTEM STREQUAL "LINUX")
        add_executable(
            ${targetProject}
            ${MAIN_SOURCES}
            ${targetSources}
        )
    elseif(OPERATING_SYSTEM STREQUAL "ANDROID")
        add_executable(
            ${targetProject}
            ${MAIN_SOURCES}
            ${targetSources}
        )
    elseif(OPERATING_SYSTEM STREQUAL "WASM")
        add_executable(
            ${targetProject}
            ${MAIN_SOURCES}
            ${targetSources}
        )
    elseif(OPERATING_SYSTEM STREQUAL "NOOP")
        add_executable(
            ${targetProject}
            ${targetSources}
        )
    endif()
endfunction()

# =============================================================

# Finalize Library
add_library(
    ${PROJECT_NAME}
    ${FILE_SOURCES}
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# =============================================================

option(BUILD_TESTS "If enabled, compile the tests." OFF)

if (BUILD_TESTS)
    MESSAGE( STATUS "Building CrossWindow Tests..." )
    # Unit Tests
    set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")
    include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
        ${PROJECT_SOURCE_DIR}/src
        )

    set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        )

    foreach(_source ${GOOGLETEST_SOURCES})
        set_source_files_properties(${_source} PROPERTIES GENERATED 1)
    endforeach()

    add_library(GoogleTest ${GOOGLETEST_SOURCES})

    # Test Sources (@TODO - replace with function or macro)
    file(GLOB_RECURSE tests_list RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.hpp
    )

    # Solution Filters
    foreach(test IN LISTS tests_list)
        get_filename_component(test_path "${test}" PATH)
        string(REPLACE "/" "\\" test_path_msvc "${test_path}")
        string(REPLACE "tests" "" test_path_final "${test_path_msvc}")
        source_group("${test_path_final}" FILES "${test}")
    endforeach()
    # Uses WinMain for windows
    xwin_add_executable(
        Tests
        1
        0
        0
        0
        "AlainGalvan"
        "${tests_list}"
        )
    
    target_link_libraries(
        Tests
        ${PROJECT_NAME}
        GoogleTest
        )
    add_dependencies(
        Tests
        ${PROJECT_NAME}
        GoogleTest
    )
    include(CTest)
    enable_testing()
    add_test(
        UnitTests 
        ${PROJECT_BINARY_DIR}/tests
    )

    target_compile_definitions(Tests PRIVATE XWIN_${OPERATING_SYSTEM}=1)

endif()

# =============================================================

# Preprocessor Definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC XWIN_${OPERATING_SYSTEM}=1)

