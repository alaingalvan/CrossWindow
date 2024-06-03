#include "WaylandWindow.h"
#include "CrossWindow/Common/WindowDesc.h"

#include <functional>

namespace xwin
{
Window::Window() {
  create(mDesc, mEventQueue);
}

Window::~Window() { close(); }

void Window::minimize() {}

void Window::maximize() {}

const WindowDesc Window::getDesc() { return mDesc; }

void Window::trackEventsAsync(
    const std::function<void(const xwin::Event e)>& fun)
{
    mCallback = fun;
}
// Executes an event callback asynchronously, use this for non-blocking
// events (resizing while rendering, etc.)
void Window::executeEventCallback(const xwin::Event e)
{
  if (mCallback) {
    mCallback(e);
  }
}

bool Window::create(const WindowDesc& desc, EventQueue& eventQueue) {
  const XWinState &xwinState = getXWinState();

  surface = wl_compositor_create_surface(xwinState.compositor);
  if (surface == nullptr) {
    return false;
  }

  shell_surface = wl_shell_get_shell_surface(shell, surface);
  if (shell_surface == nullptr) {
    return false;
  }

  wl_shell_surface_set_toplevel(shell_surface);
  wl_shell_surface_set_title(shell_surface, mDesc.title.c_str());

  return true;
}

void Window::close() {
}
}
