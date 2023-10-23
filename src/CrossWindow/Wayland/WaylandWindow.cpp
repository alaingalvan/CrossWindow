#include "WaylandWindow.h"
#include "CrossWindow/Common/WindowDesc.h"

#include <functional>

namespace xwin
{
Window::Window() { create(); }

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
    if (mCallback) mCallback(e);
}

bool Window::create(const WindowDesc& desc, EventQueue& eventQueue) {}

bool Window::close() {}
}
