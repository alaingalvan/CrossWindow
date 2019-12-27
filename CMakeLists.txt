# Project Info
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
cmake_policy(VERSION 3.6)
project(CrossWindow)
enable_language(C)
enable_language(CXX)

# CMake Settings
set(CMAKE_SUPPRESS_REGENERATION true)
set(DCMAKE_GENERATOR_PLATFORM "x64")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =============================================================

# Options
set(XWIN_API AUTO CACHE STRING "A more specific platform selector to choose from, choose the exact OS API to use, can be WIN32, UWP, COCOA, APPKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP.")
set_property(
    CACHE
    XWIN_API PROPERTY
    STRINGS AUTO WIN32 UWP COCOA APPKIT XCB XLIB MIR WAYLAND ANDROID WASM NOOP
)

set(XWIN_OS AUTO CACHE STRING "Optional: Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM.") 
set_property(
    CACHE
    XWIN_OS PROPERTY
    STRINGS AUTO WINDOWS MACOS LINUX ANDROID IOS WASM NOOP
)

if( NOT (XWIN_OS STREQUAL "AUTO") AND XWIN_API STREQUAL "AUTO")
    if(XWIN_OS STREQUAL "WINDOWS")
        set(XWIN_API "WIN32")
    elseif(XWIN_OS STREQUAL "MACOS")
        set(XWIN_API "COCOA")
    elseif(XWIN_OS STREQUAL "LINUX")
        set(XWIN_API "XLIB")
    elseif(XWIN_OS STREQUAL "ANDROID")
        set(XWIN_API "ANDROID")
    elseif(XWIN_OS STREQUAL "IOS")
        set(XWIN_API "UIKIT")
    elseif(XWIN_OS STREQUAL "WASM")
        set(XWIN_API "WASM")
    elseif(XWIN_OS STREQUAL "NOOP")
        set(XWIN_API "NOOP")
    else()
        message( SEND_ERROR "XWIN_OS can only be either AUTO, NOOP, WINDOWS, MACOS, LINUX, ANDROID, IOS, or WASM.")
    endif()
endif()

if(XWIN_API STREQUAL "AUTO")
    if (WIN32)
    set(XWIN_API "WIN32" CACHE STRING "A more specific platform selector to choose from, choose the exact OS protocol to use, can be WIN32, UWP, COCOA, APPKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP." FORCE)
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(XWIN_API "COCOA" CACHE STRING "A more specific platform selector to choose from, choose the exact OS protocol to use, can be WIN32, UWP, COCOA, APPKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP." FORCE)
    elseif (UNIX)
    set(XWIN_API "XCB" CACHE STRING "A more specific platform selector to choose from, choose the exact OS protocol to use, can be WIN32, UWP, COCOA, APPKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP." FORCE)
    endif()
endif()

set(XWIN_API_PATH "Noop")

if(XWIN_API STREQUAL "WIN32")
    set(XWIN_API_PATH "Win32")
elseif(XWIN_API STREQUAL "UWP")
    set(XWIN_API_PATH "UWP")
elseif(XWIN_API STREQUAL "COCOA")
    set(XWIN_API_PATH "Cocoa")
elseif(XWIN_API STREQUAL "XCB")
    set(XWIN_API_PATH "XCB")
elseif(XWIN_API STREQUAL "ANDROID")
    set(XWIN_API_PATH "Android")
elseif(XWIN_API STREQUAL "UIKIT")
    set(XWIN_API_PATH "UIKit")
elseif(XWIN_API STREQUAL "WASM")
    set(XWIN_API_PATH "WASM")
elseif(XWIN_API STREQUAL "NOOP")
    set(XWIN_API_PATH "Noop")
else()
    message( SEND_ERROR "XWIN_API can only be either AUTO, NOOP, WIN32, UWP, COCOA, APPKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, or WASM.")
endif()

message( STATUS "Building CrossWindow for " ${XWIN_API_PATH} )

# =============================================================

# Sources

file(GLOB_RECURSE FILE_SOURCES RELATIVE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/CrossWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/CrossWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Common/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Common/*.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Common/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Main/Main.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/${XWIN_API_PATH}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/${XWIN_API_PATH}/*.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/${XWIN_API_PATH}/*.h
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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Main/${XWIN_API_PATH}Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow/Main/${XWIN_API_PATH}Main.mm
)

set(XMAIN_SOURCES ${MAIN_SOURCES} CACHE STRING "Global Variable - The source files for the currently active protocol.")

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
    set(XWIN_FILES "${XMAIN_SOURCES}" "${targetSources}")

    if(XWIN_API STREQUAL "WIN32" OR XWIN_API STREQUAL "UWP")
        add_executable(
            ${targetProject}
            WIN32
            "${XWIN_FILES}"
        )
    elseif(XWIN_API STREQUAL "COCOA" OR XWIN_API STREQUAL "UIKIT")
        add_executable(
            ${targetProject}
            MACOSX_BUNDLE
            ${XWIN_FILES}

        )
    elseif(XWIN_API STREQUAL "XCB")
        add_executable(
            ${targetProject}
            ${XWIN_FILES}
        )
    elseif(XWIN_API STREQUAL "ANDROID")
        add_executable(
            ${targetProject}
            ${XWIN_FILES}
        )
    elseif(XWIN_API STREQUAL "WASM")
        add_executable(
            ${targetProject}
            ${XWIN_FILES}
        )
    elseif(XWIN_API STREQUAL "NOOP")
        add_executable(
            ${targetProject}
            ${XWIN_FILES}
        )
    endif()

    target_compile_definitions(${targetProject} PRIVATE XWIN_${XWIN_API}=1)

endfunction()

# =============================================================

# Finalize Library
add_library(
    ${PROJECT_NAME}
    ${FILE_SOURCES}
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)

# =============================================================

# CrossWindow Dependencies
if(XWIN_API STREQUAL "COCOA")
  add_definitions("-x objective-c++")
  find_library(COCOA_LIBRARY Cocoa)
  find_library(QUARTZ_LIBRARY QuartzCore)
  target_link_libraries(
    ${PROJECT_NAME}
    ${COCOA_LIBRARY}
    ${QUARTZ_LIBRARY}
)
endif()
if(XWIN_API STREQUAL "UIKIT")
  add_definitions("-x objective-c++")
  find_library(UIKIT_LIBRARY UIKit)
  target_link_libraries (
      ${PROJECT_NAME}
      ${UIKIT_LIBRARY}
      )
endif()

# =============================================================

# Preprocessor Definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC XWIN_${XWIN_API}=1)

# =============================================================

option(XWIN_TESTS "If enabled, compile the tests." OFF)

if (XWIN_TESTS)
    MESSAGE( STATUS "Building CrossWindow Tests..." )

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # we use this to get code coverage
    if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()

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

    xwin_add_executable(
        Tests
        "${tests_list}"
        )

    if(NOT MSVC)
        find_package(Threads REQUIRED)
        set(PThreadLib -pthread)
    endif()
    
    target_link_libraries(
        Tests
        ${PROJECT_NAME}
        ${PThreadLib}
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
        NAME UnitTests
        COMMAND Tests
    )

    set_property(TARGET GoogleTest PROPERTY FOLDER "Dependencies")

endif()