## Windows

```cpp
const xwin::State& state = xwin::getXWinState();

#if defined(XWIN_WINDOWS)
  HINSTANCE hinstance = state.hinstance;
  HWND hwnd = window->hwnd;
#endif

```

## MacOS

On MacOS, CrossWindow creates an `NSApplication` in its MacOS specific main function, and a pointer to this is accessible from `xwin::getXWinState()`.

The `NSApplication` is used to create `NSWindow` and `NSView` objects, with Views inside of Windows on MacOS.

A `xwin::MacOSWindow` object is accessible by grabbing a window's delegate:

```cpp
const xwin::State& state = xwin::getXWinState();

#if defined(XWIN_MACOS)
  NSApplication app = state.application;
  NSWindow* window = window->window;
  NSView* view = window->view;
#endif

```
