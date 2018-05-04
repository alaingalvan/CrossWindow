# CrossWindow

[![cmake-img]][cmake-url]
[![License][license-img]][license-url]
[![Unit Tests][travis-img]][travis-url]
[![Coverage Tests][codecov-img]][codecov-url]

A basic cross platform system abstraction library for managing windows and performing OS tasks. 

## Features

- Window Creation

- Basic Input (Keyboard, Mouse, Touch)

- OS Dialogs

- Platform specific features (Mac Transparency, Touch Bar, etc.)

## Supports

- 🖼️ Windows

- 🍎 Mac (In Progress)

- 🐧 Linux (In Progress)

- 🤖 Android (In Progress)

- 📱 iOS (In Progress)

- 🌐 WebAssembly (In Progress)

## Installation

First add the repo as a submodule in your dependencies folder such as `external/`:

```
cd external
git submodule add https://github.com/alaingalvan/CrossWindow.git
```

Then in your `CMakeLists.txt` file, include the following:

```cmake
# ⬇ Add your dependency:
add_subdirectories(external/CrossWindow)

# ⚪ Setup CrossWindow for OS specific functionality
xwin_setup(
    # Major Minor Patch Build
    1 0 0 0
    # Company Name
    "MyCompany"     
    # File Icon Path
    # Cross Window will look for OS specific icons with the name corresponding to the icon size.
    "${CMAKE_CURRENT_SOURCE_DIR}/OsFiles/Icons"
)

# ❎ When creating your executable use CrossWindow's abstraction function:
xwin_add_executable(
    # Target
    ${PROJECT_NAME}
    # Source Files (make sure to surround in quotations)
    "${SOURCE_FILES}"
)

# 🔗 Link CrossWindow to your project:
target_link_libraries(
    ${PROJECT_NAME}
    CrossWindow
)
```

## Usage

First create a main delegate function `xmain` where you'll put your application logic:

```cpp
#include "CrossWindow/CrossWindow.h"

void xmain(int argc, const char* argv[])
{
    // Create Window Object
    xwin::WindowDesc windowDesc;
    windowDesc.name = "Test";
    windowDesc.title = "My Title";
    windowDesc.visible = true;
    windowDesc.width = 1280;
    windowDesc.height = 720;

    xwin::Window window;
    if (window.create(windowDesc))
    {
        while (window.eventLoop())
        {
            // Run renderer logic here
        }
    }
}
```

This `xmain` function will be called from a platform specific main function that will be included in your main project by CMake. If you ever need to access something from that main function for whatever reason, you'll find it in `xwin::getXWinState()`.

For more examples visit the [Documentation](/docs).

## Development

Be sure to have [CMake](https://cmake.org) Installed.

| CMake Options | Description |
|:-------------:|:-----------:|
| `XWIN_TESTS` | Whether or not unit tests are enabled. Defaults to `OFF`, Can be `ON` or `OFF`. |
| `OPERATING_SYSTEM` | What Operating System to build for, defaults to `AUTO`, can be `NOOP`, `WINDOWS`, `MACOS`, `LINUX`, `ANDROID`, `IOS`, `WASM`. |

We would recommend making a folder where solution files will be built to to avoid making your file system look too messy, such as `visualstudio/` or `xcode/` depending on the platform you're building for. `cd` to that directory and type in your terminal:

```bash
# ⚗️ To build solution with tests
cmake -DXWIN_TESTS=ON ..

# Or...

cmake -G Xcode -DXWIN_TESTS=ON -DOPERATING_SYSTEM=MACOS ..
```

Whenever you add new files to the project, run `cmake ..`, and if you edit the `CMakeLists.txt` file be sure to delete your `CMakeCache.txt` and `CMakeFiles/` and run Cmake again.

## License

CrossWindow is licensed as either **MIT** or **Apache-2.0**, whichever you would prefer.

[cmake-img]: https://img.shields.io/badge/cmake-3.9-1f9948.svg?style=flat-square
[cmake-url]: https://cmake.org/
[license-img]: https://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT
[travis-img]: https://img.shields.io/travis/alaingalvan/crosswindow.svg?style=flat-square
[travis-url]: https://travis-ci.org/alaingalvan/crosswindow
[codecov-img]:https://img.shields.io/codecov/c/github/alaingalvan/crosswindow.svg?style=flat-square
[codecov-url]: https://codecov.io/gh/alaingalvan/crosswindow