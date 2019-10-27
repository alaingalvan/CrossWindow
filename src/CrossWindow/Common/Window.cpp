#include "Window.h"

namespace xwin
{
Window::Window() {}

Window::~Window() { close(); }

bool Window::create(const WindowDesc& desc, EventQueue& queue)
{
    mDesc = desc;
    return mDelegate.create(mDesc, queue, this);
}

void Window::showMouse(bool show) {}

void Window::setSize(const UVec2& size)
{
    mDelegate.setWindowSize(size.x, size.y);
}

void Window::setMousePosition(const UVec2 position)
{
    mDelegate.setMousePosition(position.x, position.y);
}

UVec2 Window::getCurrentDisplaySize()
{
    return mDelegate.getCurrentDisplaySize();
}

void Window::close() { mDelegate.close(); }

WindowDelegate& Window::getDelegate() { return mDelegate; }

WindowDesc Window::getDesc() const { return mDesc; }
}
