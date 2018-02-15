# CrossWindow

[![cmake-img]][cmake-url]
[![License][license-img]][license-url]
[![Unit Tests][travis-img]][travis-url]
[![Coverage Tests][codecov-img]][codecov-url]

A basic cross platform windowing library for Windows, Mac, Linux, Android, iOS, and WebAssembly.

- Window Creation

- Basic Input

- File Systems

```cpp
#include "CrossWindow/CrossWindow.h"

xmain(MainArgs)
{
  xwin::init(MainArgs);

  xwin::Window window();

  while(window.eventLoop())
  {
    // ...
  }
}
```

### Checking Inputs

```cpp
#include "CrossWindow/CrossWindow.h"
#include <iostream>

xmain(MainArgs)
{
  xwin::init(MainArgs);

  xwin::WindowDesc desc();

  xwin::Window window(desc);

  while (window.eventLoop())
  {
    window.subscribe(xwin::Event::MouseMove, [](xwin::MouseMove e) {
      std::cout << "X: " << e.x << "Y: " << e.y << "\n";
    });

    window.subscribe(xwin::Event::MouseClick, [](xwin::MouseClick e) {
      std::cout << "Left: " << e.left << "Right: " << e.right << "\n";
    });

    window.subscribe(xwin::Event::KeyPress, [](xwin::KeyPress e) {
      std::cout << "Key Press: " << xwin::KeyString[e.keycode] << "\n";
    });

    window.subscribe(xwin::Event::KeyRelease, []() {
      std::cout << "Key Release: " << xwin::KeyString[e.keycode] << "\n";
    });

    window.subscribe(xwin::Event::Touch, [](xwin::Touch e) {
      for (auto it = e.touches.begin(); it != e.touches.end() ++it)
      {
        std::cout << "Touch " << it - e.touches.begin() << ": X: " << it->x << " Y: " << it-> y<< "\n";
      }
    });

    window.subscribe(xwin::Event::Resize, []() {
      std::cout << "Resized!"
    });

    window.subscribe(xwin::Event::Maximize, []() {
      std::cout << "Maximized!";
    });

    window.subscribe(xwin::Event::Minimize, []() {
      std:cout << "Minimized!";
    });

    window.subscribe(xwin::Event::Close, []() {
      window.close();
    });


  }
}
```

### Creating Multiple Windows

```cpp
#include "CrossWindow/CrossWindow.h"

xmain(MainArgs)
{
  xwin::init(MainArgs);

  xwin::WindowDesc desc1();
  xwin::Window window1(desc);

  xwin::WindowDesc desc2();
  desc2.monitor = 1;
  xwin::Window window2(desc);

  while (window1.eventLoop() && window2.eventLoop())
  {
    // Update engine
  }
}
```

[cmake-img]: https://img.shields.io/badge/cmake-3.9-1f9948.svg?style=flat-square
[cmake-url]: https://cmake.org/
[license-img]: https://img.shields.io/:license-©-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT
[travis-img]: https://img.shields.io/travis/alaingalvan/crosswindow.svg?style=flat-square
[travis-url]: https://travis-ci.org/alaingalvan/crosswindow
[codecov-img]:https://img.shields.io/codecov/c/github/alaingalvan/crosswindow.svg?style=flat-square
[codecov-url]: https://codecov.io/gh/alaingalvan/crosswindow