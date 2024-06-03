cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
cmake_policy(VERSION 3.18)
project(CrossWindow)
enable_language(C)
enable_language(CXX)

# CMake Settings
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# =============================================================

# Options
set(XWIN_API AUTO CACHE STRING "A more specific platform selector to choose from, choose the exact OS API to use, can be WIN32, UWP, COCOA, UIKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP.")
set_property(
    CACHE
    XWIN_API PROPERTY
    STRINGS AUTO WIN32 UWP COCOA UIKIT XCB XLIB MIR WAYLAND ANDROID WASM NOOP
)

set(XWIN_OS AUTO CACHE STRING "Optional: Choose the OS to build for, defaults to AUTO, but can be WINDOWS, MACOS, LINUX, ANDROID, IOS, WASM.")
set_property(
    CACHE
    XWIN_OS PROPERTY
    STRINGS AUTO WINDOWS MACOS LINUX ANDROID IOS WASM NOOP
)

function(deduce_linux_display_server)
  message( STATUS "XDG session type: " "$ENV{XDG_SESSION_TYPE}" )
  if ("$ENV{XDG_SESSION_TYPE}" STREQUAL "wayland")
    set(XWIN_API "WAYLAND" PARENT_SCOPE)
  elseif ("$ENV{XDG_SESSION_TYPE}" STREQUAL "x11")
    set(XWIN_API "XCB" PARENT_SCOPE)
  else()
    execute_process (
      COMMAND bash -c "env | awk -F= '$2 ~ /wayland/ {count++} END {print count}'"
      OUTPUT_VARIABLE WaylandCount
      )
    execute_process (
      COMMAND bash -c "env | awk -F= '$2 ~ /x11/ {count++} END {print count}'"
      OUTPUT_VARIABLE X11Count
      )
    message(STATUS "Display server counts: " ${X11Count} " " ${WaylandCount})
    if (${X11Count} LESS ${WaylandCount})
      set(XWIN_API "WAYLAND" PARENT_SCOPE)
    else()
      set(XWIN_API "XCB" PARENT_SCOPE)
    endif()
  endif()
endfunction()

if( NOT (XWIN_OS STREQUAL "AUTO") AND XWIN_API STREQUAL "AUTO")
    if(XWIN_OS STREQUAL "WINDOWS")
        set(XWIN_API "WIN32")
    elseif(XWIN_OS STREQUAL "MACOS")
        set(XWIN_API "COCOA")
    elseif(XWIN_OS STREQUAL "LINUX")
        deduce_linux_display_server()
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
    if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
      set(XWIN_API "WIN32" CACHE STRING "A more specific platform selector to choose from, choose the exact OS protocol to use, can be WIN32, UWP, COCOA, UIKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP." FORCE)
    elseif (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
      set(XWIN_API "COCOA" CACHE STRING "A more specific platform selector to choose from, choose the exact OS protocol to use, can be WIN32, UWP, COCOA, UIKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, WASM, NOOP." FORCE)
    elseif (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
      deduce_linux_display_server()
    endif()
endif()

set(XWIN_API_PATH "Noop")

if(XWIN_API STREQUAL "WIN32")
    set(XWIN_API_PATH "Win32")
elseif(XWIN_API STREQUAL "UWP")
    set(XWIN_API_PATH "UWP")
elseif(XWIN_API STREQUAL "COCOA")
    set(XWIN_API_PATH "Cocoa")
elseif(XWIN_API STREQUAL "UIKIT")
    set(XWIN_API_PATH "UIKit")
elseif(XWIN_API STREQUAL "XCB")
    set(XWIN_API_PATH "XCB")
elseif(XWIN_API STREQUAL "XLIB")
    set(XWIN_API_PATH "XLib")
elseif(XWIN_API STREQUAL "WAYLAND")
    set(XWIN_API_PATH "Wayland")
elseif(XWIN_API STREQUAL "ANDROID")
    set(XWIN_API_PATH "Android")
elseif(XWIN_API STREQUAL "UIKIT")
    set(XWIN_API_PATH "UIKit")
elseif(XWIN_API STREQUAL "WASM")
    set(XWIN_API_PATH "WASM")
elseif(XWIN_API STREQUAL "NOOP")
    set(XWIN_API_PATH "Noop")
else()
    message( SEND_ERROR "Detected: ${XWIN_API}; XWIN_API can only be either AUTO, NOOP, WIN32, UWP, COCOA, UIKIT, XCB, XLIB, MIR, WAYLAND, ANDROID, or WASM.")
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

set(XWIN_DEFINITIONS XWIN_${XWIN_API}=1 CACHE STRING "Global Variable - The compile definitions for the currently active protocol.")

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
set_target_properties(
    ${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "2"
)
elseif(XWIN_API STREQUAL "UIKIT")
    add_definitions("-x objective-c++")
    # Locate system libraries on iOS
    find_library(UIKIT UIKit)
    find_library(METALKIT_LIBRARY MetalKit)

    find_library(FOUNDATION Foundation)
    find_library(MOBILECORESERVICES MobileCoreServices)
    find_library(CFNETWORK CFNetwork)
    find_library(SYSTEMCONFIGURATION SystemConfiguration)

    target_link_libraries(
    ${PROJECT_NAME}
    ${UIKIT}
    ${METALKIT_LIBRARY}
    ${FOUNDATION}
    ${CFNETWORK}
    ${SYSTEMCONFIGURATION}
    )
    set_target_properties(
    ${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "2"
    )
    # Turn on ARC
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-arc")
elseif(XWIN_API STREQUAL "XLIB")
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        message("Found X11 Libraries.")
        message("X11 includes = ${X11_INCLUDE_DIR}")
        message("X11 Libraries = ${X11_LIBRARIES}")
        target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
        target_include_directories(${PROJECT_NAME} PUBLIC ${X11_INCLUDE_DIR})
    endif()
elseif(XWIN_API STREQUAL "WAYLAND")
    find_package(Wayland REQUIRED)
    if(Wayland_FOUND)
        message("Found Wayland Libraries.")
        message("Wayland includes = ${Wayland_INCLUDE_DIRS}")
        message("Wayland Libraries = ${Wayland_LIBRARIES}")
        target_link_libraries(${PROJECT_NAME} ${Wayland_LIBRARIES})
        target_include_directories(${PROJECT_NAME} PUBLIC ${Wayland_INCLUDE_DIRS})
    endif()
elseif(XWIN_API STREQUAL "XCB")
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        message("Found XCB Libraries.")
        message("XCB Include Path = ${X11_xcb_INCLUDE_PATH}")
        message("XCB Lib = ${X11_xcb_LIB}")
        target_link_libraries(${PROJECT_NAME} ${X11_xcb_LIB})
        target_include_directories(${PROJECT_NAME} PUBLIC ${X11_xcb_INCLUDE_PATH})
    endif()
endif()
# =============================================================

# Preprocessor Definitions
target_compile_definitions(${PROJECT_NAME} PUBLIC XWIN_${XWIN_API}=1)
