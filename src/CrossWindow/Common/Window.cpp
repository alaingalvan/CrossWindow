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
        return mDelegate.create(mDesc, queue);
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
