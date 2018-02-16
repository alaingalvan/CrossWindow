#include "Window.h"

namespace xwin
{
    Window::Window(const WindowDesc& desc) : mDesc(desc)
    {

    }
    Window::~Window()
    {
    }
    bool Window::eventLoop()
    {
        return false;
    }
}