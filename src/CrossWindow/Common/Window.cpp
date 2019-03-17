#include "Window.h"

namespace xwin
{
    Window::Window()
    {
    }

    Window::~Window()
    {
        close();
    }

    bool Window::create(const WindowDesc& desc, EventQueue& queue)
    {
        mDesc = desc;
        return mDelegate.create(mDesc, queue, this);
    }

    void Window::setMousePosition(unsigned x, unsigned y)
    {
        mDelegate.setMousePosition(x, y);
    }

    UVec2 Window::getCurrentDisplaySize()
    {
        return mDelegate.getCurrentDisplaySize();
    }

    void Window::close()
    {
        mDelegate.close();
    }

    WindowDelegate& Window::getDelegate()
    {
        return mDelegate;
    }

    WindowDesc Window::getDesc() const
    {
        return mDesc;
    }
}
