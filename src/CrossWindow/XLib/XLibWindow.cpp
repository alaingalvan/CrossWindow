#include "XLibWindow.h"

namespace xwin
{
bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
    XInitThreads();
    display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    Visual* visual = DefaultVisual(display, screen);
    int depth = DefaultDepth(display, screen);

    Colormap colormap = XCreateColormap(display, RootWindow(display, screen),
                                        visual, AllocNone);

    XSetWindowAttributes windowAttributes = {};
    windowAttributes.colormap = colormap;
    windowAttributes.background_pixel = 0xFFFFFFFF;
    windowAttributes.border_pixel = 0;
    windowAttributes.event_mask =
        KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;

    window =
        XCreateWindow(display, RootWindow(display, screen), 0, 0, desc.width,
                      desc.height, 0, depth, InputOutput, visual,
                      CWBackPixel | CWBorderPixel | CWEventMask | CWColormap,
                      &windowAttributes);

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
    XFlush(display);
}

bool Window::destroy() { XDestroyWindow(display, window); }
}