# Project Info
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
cmake_policy(VERSION 3.9)
project(CrossWindow)
enable_language(C)
enable_language(CXX)

# CMake Settings
set(CMAKE_SUPPRESS_REGENERATION true)
set(DCMAKE_GENERATOR_PLATFORM "x64")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_AUTOMOC ON)

# =============================================================

# Options
set(OPERATING_SYSTEM AUTO CACHE STRING "Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM") 
set_property(CACHE OPERATING_SYSTEM PROPERTY STRINGS AUTO VULKAN OPENGL DIRECTX METAL NOOP)

if(OPERATING_SYSTEM STREQUAL "AUTO")
    if (WIN32)
    set(OPERATING_SYSTEM "WINDOWS" CACHE STRING "Choose the current graphics API, defaults to AUTO, but can be VULKAN, OPENGL, DIRECTX, METAL, or NOOP" FORCE)
    endif (WIN32)
    if (APPLE)
    set(OPERATING_SYSTEM "MACOS" CACHE STRING "Choose the current graphics API, defaults to AUTO, but can be VULKAN, OPENGL, DIRECTX, METAL, or NOOP" FORCE)
    endif (APPLE)
    if (UNIX)
    set(OPERATING_SYSTEM "LINUX" CACHE STRING "Choose the current graphics API, defaults to AUTO, but can be VULKAN, OPENGL, DIRECTX, METAL, or NOOP" FORCE)
    endif (UNIX)
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

file(GLOB_RECURSE mag_sources RELATIVE
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
foreach(source IN LISTS mag_sources)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    string(REPLACE "src" "" source_path_final "${source_path_msvc}")
    source_group("${source_path_final}" FILES "${source}")
endforeach()

# =============================================================

# Finalize Library
add_library(
    ${PROJECT_NAME}
    ${mag_sources}
    )

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

    if(WIN32)
        add_executable(
            Tests
            WIN32
            ${tests_list}
            )
    else()
        add_executable(
            Tests
            ${tests_list}
            )
    endif()
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
        unit 
        ${PROJECT_BINARY_DIR}/tests
    )

    target_compile_definitions(Tests PRIVATE XWIN_${OPERATING_SYSTEM}=1)

endif()

# =============================================================

# Preprocessor Definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE XWIN_${OPERATING_SYSTEM}=1)

