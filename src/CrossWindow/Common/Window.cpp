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
        mDesc = desc;
        return mDelegate.create(mDesc);
    }

    std::vector<EventType>& Window::pollEvents()
    {
        return mDelegate.pollEvents();
    }
    void Window::close()
    {
        mDelegate.close();
    }
}