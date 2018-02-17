#include "Window.h"

namespace xwin
{
    Window::Window()
    {
    }

    Window::~Window()
    {
    }

    bool Window::create(const WindowDesc& desc)
    {
        return mDelegate.create(desc);
    }

    bool Window::eventLoop()
    {
        return mDelegate.eventLoop();
    }
}