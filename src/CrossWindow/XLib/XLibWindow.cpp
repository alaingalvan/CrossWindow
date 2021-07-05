#include "XLibWindow.h"

namespace xwin
{
bool Window::create(const WindowDesc& desc, EventQueue& eventQueue)
{
    XInitThreads();
    display = XOpenDisplay(NULL);
    long visualMask = VisualScreenMask;
    int numberOfVisuals;
    XVisualInfo vInfoTemplate = {};
    vInfoTemplate.screen = DefaultScreen(display);
    XVisualInfo* visualInfo =
        XGetVisualInfo(display, visualMask, &vInfoTemplate, &numberOfVisuals);

    Colormap colormap =
        XCreateColormap(display, RootWindow(display, vInfoTemplate.screen),
                        visualInfo->visual, AllocNone);

    XSetWindowAttributes windowAttributes = {};
    windowAttributes.colormap = colormap;
    windowAttributes.background_pixel = 0xFFFFFFFF;
    windowAttributes.border_pixel = 0;
    windowAttributes.event_mask =
        KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;

    window = XCreateWindow(
        display, RootWindow(display, vInfoTemplate.screen), 0, 0, desc.width,
        desc.height, 0, visualInfo->depth, InputOutput, visualInfo->visual,
        CWBackPixel | CWBorderPixel | CWEventMask | CWColormap,
        &windowAttributes);

    XSelectInput(display, *window, ExposureMask | KeyPressMask);
    XMapWindow(display, *window);
    XFlush(display);
}

bool Window::destroy() { XDestroyWindow(display, window); }
}