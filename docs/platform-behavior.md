## Windows

```cpp
xwin::WindowDelegate& delegate = window.getDelegate();
const xwin::State& state = xwin::getXWinState();

#if defined(XWIN_WINDOWS)
  HINSTANCE hinstance = state.hinstance;
  HWND hwnd = delegate.hwnd;
#endif

```

## MacOS

On MacOS, CrossWindow creates an `NSApplication` in its MacOS specific main function, and a pointer to this is accessible from `xwin::getXWinState()`. 

The `NSApplication` is used to create `NSWindow` and `NSView` objects, with Views inside of Windows on MacOS.

A `xwin::MacOSWindow` object is accessible by grabbing a window's delegate:

```cpp
WindowDelegate& delegate = window.getDelegate();
const xwin::State& state = xwin::getXWinState();

#if defined(XWIN_MACOS)
  NSApplication app = state.application;
  NSWindow* window = delegate.window;
  NSView* view = delegate.view;
#endif

```
